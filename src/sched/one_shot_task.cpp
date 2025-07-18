#include "sched/one_shot_task.h"
#include "spdlog/spdlog.h"

EAR::Schedule::OneShotTask::OneShotTask(const std::string &name) : EAR::Schedule::Task(name)
{
}

EAR::Schedule::OneShotTask::~OneShotTask()
{
}

void EAR::Schedule::OneShotTask::execute(void) {
  std::unique_lock<std::mutex> ulock(m_mutex);

  // signal readiness for start function
  m_task_ready.store(true, std::memory_order_release); 
  m_cond_var->wait(ulock);
  std::this_thread::sleep_for(std::chrono::microseconds(m_offset));
    
  cycle();

  spdlog::debug("task {} is being stopped", getName());
    
  return;
}
