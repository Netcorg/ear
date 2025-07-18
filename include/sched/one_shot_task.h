/**
 * @file one_shot_task.h
 * @brief one shot task class that extends asynchronizable interface
 * Time-stamp: <2025-02-19 21:44:08 boo>
 */

#pragma once

#include "task.h"

namespace EAR {
  namespace Schedule {
    class OneShotTask : public Task {
    public:
      /// constructor
      /// @param [in] name - name of one shot task
      explicit OneShotTask(const std::string &name);
      /// destructor
      virtual ~OneShotTask();

    protected:
      /// function that calls cycle() function according to one shoting task algorithm
      /// @remark cycle function determines execute function body, because it is thoroughly
      /// dependent to cycle implementation details, therefore if cycle is one cycle task,
      /// the function executes once, if cycle is blocking task, the function waits until
      /// cycle() terminates, or stop function is called
      virtual void execute(void) override;
    };
  }
}
