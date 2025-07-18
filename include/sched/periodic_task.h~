/**
 * @file task.h
 * @brief base task class that extends synchronizable interface
 * Time-stamp: <2025-02-19 21:44:08 boo>
 */

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

/// minimum period of task in usec
#define TASK_MIN_PERIOD (100000U)

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
      /// function that sets period of the task
      /// @param [in] period - task period in usec
      void setPeriod(const std::chrono::microseconds period);	    
      /// function that sets offset of the task
      /// @param [in] offset - offset to sleep before execution in usec
      void setOffset(const std::chrono::microseconds offset);
      /// function that sets condition variable
      /// @param [in] cond_var - condition variable instance
      void setConditionVariable(std::condition_variable *cond_var);
      /// function that starts task
      /// @return true if the task is started, otherwise false
      bool start(void);
      /// function that stops task
      /// @return true if the task is stopped, otherwise false
      bool stop(void);
      /// function that implements execution body of task, it calls cycle() according to timing parameter
      /// @remark developer is thoroughly responsible for any deadline of the task, it should be guaranteed
      /// that the task performs its one cycle within period. The offset parameter is used to sleep the task
      /// once before it starts execution, there is no more usage for the offset for another sleep operation
      void execute(void);
      /// function that overload equality operator for class instance
      /// @remark equality check is done according to task name
      /// @param [in] other - right operand of equality operator
      /// @return true if this is equal to other, otherwise false
      bool operator==(const Task &other) const;
      /// function that overload not equal operator for class instance
      /// @param [in] other - right operand of equality operator
      /// @return true if this is not equal to other, otherwise false
      bool operator!=(const Task &other) const;

      /// function that initializes task
      /// @return true if the initialization done successfully, otherwise false
      virtual bool initialize(void) = 0;	    
      /// function that performs one cycle of task
      /// @remark it is supposed to be implemented by task user
      virtual void cycle(void) = 0;

    private:
      /// task name
      std::string m_name;
      /// task period in usec
      std::chrono::microseconds m_period = std::chrono::microseconds(TASK_MIN_PERIOD);
      /// task start offset in usec
      std::chrono::microseconds m_offset = std::chrono::microseconds(0U);
      /// thread instance
      std::thread m_task;
      /// start mutex used to give start to the task
      std::mutex m_mutex;
      /// start condition flag for the thread
      std::condition_variable *m_cond_var = nullptr;
      /// task ready flag to wait until thread creation is done
      std::atomic<bool> m_task_ready;
      /// running flag
      bool m_is_running = false;
    };
  }
}
