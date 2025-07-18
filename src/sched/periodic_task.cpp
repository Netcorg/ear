#include "sched/periodic_task.h"
#include "spdlog/spdlog.h"

EAR::Schedule::PeriodicTask::PeriodicTask(const std::string &name) : EAR::Schedule::Task(name)
{
}

EAR::Schedule::PeriodicTask::~PeriodicTask()
{
}

void EAR::Schedule::PeriodicTask::setPeriod(const std::chrono::microseconds period) {
  m_period = std::chrono::microseconds(period);
  return;
}

void EAR::Schedule::PeriodicTask::execute(void) {
  std::chrono::steady_clock::time_point begin;
  std::chrono::steady_clock::time_point end;
  std::chrono::microseconds elapsed;
  std::unique_lock<std::mutex> ulock(m_mutex);

  // signal readiness for start function
  m_task_ready.store(true, std::memory_order_release);
  
  m_cond_var->wait(ulock);
  std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    
  do {
    begin = std::chrono::steady_clock::now();
    cycle();
    end = std::chrono::steady_clock::now();
	
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    if (elapsed <= m_period) {
      std::this_thread::sleep_for(std::chrono::microseconds(m_period - elapsed));
    }
    else {
      spdlog::error("deadline missed for task {}", getName());
      std::this_thread::sleep_for(std::chrono::microseconds(m_period - (elapsed % m_period)));
    }
  } while (m_is_running);

  spdlog::debug("task {} is being stopped", getName());
    
  return;
}
