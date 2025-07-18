/**
 * @file scheduler.h
 * @brief task scheduler class that allocates memory for tasks, starts and stops them
 * Time-stamp: <2025-02-19 23:22:10 boo>
 */

#pragma once

#include <list>
#include "periodic_task.h"
#include "one_shot_task.h"

namespace EAR {
  namespace Schedule {
    /// scheduler type
    enum Type {
      ST_DETACHED,
      ST_SYNCHED
    };
	
    class Scheduler {
    public:
      /// constructor
      /// @param [in] name - scheduler name
      Scheduler(const std::string &name);	    
      /// destructor
      virtual ~Scheduler();
      /// function that gets scheduler name
      /// @return scheduler name
      std::string getName(void) const;
      /// function that sets scheduler  type
      /// @param [in] type - flag to set scheduler type
      void setType(Type type);      
      /// function that adds one shot task into the scheduling
      /// @param [in] task - task pointer
      /// @param [in] offset - task start offset in usec
      /// @return true if the task is added into the scheduler, otherwise false
      bool add(OneShotTask *task, const uint32_t offset);
      /// function that adds periodic task into the scheduling
      /// @param [in] task - task pointer
      /// @param [in] period - task period in usec
      /// @param [in] offset - task start offset in usec
      /// @return true if the task is added into the scheduler, otherwise false
      bool add(PeriodicTask *task, const uint32_t period, const uint32_t offset);
      /// function that runs the scheduler
      /// @pre the scheduler must be initialized firstly
      /// @return true if the scheduler starts, otherwise false
      bool start(void);
      /// function that terminates the scheduler
      /// @pre the scheduler must be run earlier
      /// @return true if the scheduler stops, otherwise false
      bool stop(void);
	    
    private:   
      /// scheduler state
      enum State {
	// refers ot idle scheduler
	SS_IDLE,
	// refers to scheduler run
	SS_RUN,
	// refers to scheduler stop
	SS_STOP
      };
      
      /// scheduler name
      std::string m_name;	    
      /// task list
      std::list<Task *> m_tasks;
      /// state for state machine of the scheduler
      State m_state = SS_IDLE;
      /// type for scheduler
      Type m_type = ST_DETACHED; 
      /// global condition variable to kick off all threads
      std::condition_variable m_cond_var;

      // prevent copyable and movable scheduler instance
      Scheduler(const Scheduler &scheduler) = delete;
      Scheduler(const Scheduler &&scheduler) = delete;
      Scheduler &operator=(const Scheduler &scheduler) = delete;
      Scheduler &operator=(const Scheduler &&scheduler) = delete;
    };
  }
}
