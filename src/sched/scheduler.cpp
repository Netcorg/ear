#include "sched/scheduler.h"
#include "spdlog/spdlog.h"

EAR::Schedule::Scheduler::Scheduler(const std::string &name) : m_name(name) {
  spdlog::debug("scheduler {} created", m_name);
}

EAR::Schedule::Scheduler::~Scheduler() {
  spdlog::debug("scheduler {} terminated", getName());
}

std::string EAR::Schedule::Scheduler::getName(void) const {
  return m_name;
}

void EAR::Schedule::Scheduler::setType(EAR::Schedule::Type type) {
  m_type = type;
  return;
}

bool EAR::Schedule::Scheduler::add(OneShotTask *task, const uint32_t offset) {
  if (nullptr == task) {
    spdlog::error("could not add null task into the {}", getName());
    return false;
  }

  if (SS_IDLE != m_state) {
    spdlog::error("could not add task into the {} when scheduler {} run", task->getName(), getName());
    return false;
  }

  task->setOffset(std::chrono::microseconds(offset));
  task->setConditionVariable(&m_cond_var);

  m_tasks.push_back(task);

  if (!task->initialize()) {
    spdlog::error("could not initialize task {} in the {}", task->getName(), getName());
    return false;	
  }

  spdlog::info("{} task is initialized", task->getName()); 
  return true;
}

bool EAR::Schedule::Scheduler::add(PeriodicTask *task, const uint32_t period, const uint32_t offset) {
  if (nullptr == task) {
    spdlog::error("could not add null task in the {}", getName());
    return false;
  }

  if (period < PERIODIC_TASK_MIN_PERIOD) {
    spdlog::error("invalid period value {} for task {}", period, task->getName());
    return false;
  }

  if (SS_IDLE != m_state) {
    spdlog::error("could not add task into the {} when scheduler {} run", task->getName(), getName());
    return false;
  }

  task->setPeriod(std::chrono::microseconds(period));
  task->setOffset(std::chrono::microseconds(offset));
  task->setConditionVariable(&m_cond_var);

  m_tasks.push_back(task);

  if (!task->initialize()) {
    spdlog::error("could not initialize task {} in {}", task->getName(), getName());
    return false;	
  }

  spdlog::info("{} task is initialized", task->getName()); 
  return true;
}

bool EAR::Schedule::Scheduler::start(void) {
  if (SS_RUN == m_state) {
    spdlog::error("could not run the scheduler {} that was already running", getName());
    return false;
  }

  for (auto &task : m_tasks) {
    if (!task->start()) {
      spdlog::critical("could not start task {}", task->getName());
    }
    else {
      spdlog::debug("task {} started", task->getName());
    }
  }

  m_cond_var.notify_all();
  m_state = SS_RUN;
  
  spdlog::debug("scheduler started");

  /// synchronize scheduler waits until its threads stop, while
  /// detached scheduler execute threads, then break waiting loop
  if (ST_SYNCHED == m_type) {
    while (SS_RUN == m_state) {
      std::this_thread::sleep_for(std::chrono::microseconds(PERIODIC_TASK_MIN_PERIOD));
    }
  }
	
  return true;
}

bool EAR::Schedule::Scheduler::stop(void) {
  if (SS_RUN != m_state) {
    spdlog::error("could not stop the scheduler {} that not running", getName());
    return false;
  }

  m_state = SS_STOP;

  for (auto &task : m_tasks) {
    if (!task->stop()) {
      spdlog::critical("could not stop task {}", task->getName());
    }
    else {
      spdlog::debug("task {} stopped", task->getName());
    }
  }

  spdlog::debug("scheduler stopped");

  return true;
}
