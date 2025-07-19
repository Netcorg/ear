/**
 * @file periodic_task.h
 * @brief periodic task class that extends synchronizable interface
 * @author boo
 */

#pragma once

#include "task.h"

/// minimum period  in usec for periodic task
#define PERIODIC_TASK_MIN_PERIOD (100000U)

namespace EAR {
  namespace Schedule {
    class PeriodicTask : public Task {
    public:
      /// constructor
      /// @param [in] name - name of periodic task
      explicit PeriodicTask(const std::string &name);
      /// destructor
      virtual ~PeriodicTask();
      /// function that sets period of the task
      /// @param [in] period - task period in usec
      void setPeriod(const std::chrono::microseconds period);

    protected:
      /// function that implements execution body of task, it calls cycle() according to timing parameter
      /// @remark developer is thoroughly responsible for any deadline of the task, it should be guaranteed
      /// that the task performs its one cycle within period. The offset parameter is used to sleep the task
      /// once before it starts execution, there is no more usage for the offset for another sleep operation
      virtual void execute(void) override;

    private:
      /// period for the task
      std::chrono::microseconds m_period = std::chrono::microseconds(PERIODIC_TASK_MIN_PERIOD);
    };
  }
}
