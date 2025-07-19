/**
 * @file task.h
 * @brief base task class that extends synchronizable interface
 * @author boo
 * @todo check usage of joinable function of thread to replace with m_is_running
 */

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <string>

namespace EAR {
  namespace Schedule {
    /// class Task implements Task interface
    class Task {
    public:
      /// constructor
      /// @param [in] name - task name
      explicit Task(const std::string &name);
      /// destructor
      virtual ~Task();
      /// function that gets task name
      /// @return task name
      std::string getName(void) const;
      /// function that sets offset of the task
      /// @param [in] offset - offset to sleep before execution in usec
      void setOffset(const std::chrono::microseconds offset);
      /// function that sets condition variable
      /// @param [in] cond_var - condition variable instance
      void setConditionVariable(std::condition_variable *cond_var);
      /// function that overload equality operator for class instance
      /// @remark equality check is done according to task name
      /// @param [in] other - right operand of equality operator
      /// @return true if this is equal to other, otherwise false
      bool operator==(const Task &other) const;
      /// function that overload not equal operator for class instance
      /// @param [in] other - right operand of equality operator
      /// @return true if this is not equal to other, otherwise false
      bool operator!=(const Task &other) const;
      /// function that starts task
      /// @return true if the task is started, otherwise false
      virtual bool start(void) final;
      /// function that stops task
      /// @return true if the task is stopped, otherwise false
      virtual bool stop(void) final;
      
      /// function that initializes task
      /// @return true if the initialization done successfully, otherwise false
      virtual bool initialize(void) = 0;
      /// function that refers to one cycle of task
      /// @remark it might be used for periodic, sporadic or one shot task
      virtual void cycle(void) = 0;

    protected:
      /// thread instance
      std::thread m_task;
      /// start mutex used to give start to the task
      std::mutex m_mutex;
      /// start condition flag for the thread
      std::condition_variable *m_cond_var = nullptr;
      /// task start offset in usec
      std::chrono::microseconds m_offset = std::chrono::microseconds(0U);
      /// task ready flag to wait until thread creation is done
      std::atomic<bool> m_task_ready;
      /// running flag
      bool m_is_running = false;

      /// function that performs execution of the task
      virtual void execute(void) = 0;

    private:
      /// task name
      std::string m_name;
    };
  }
}
