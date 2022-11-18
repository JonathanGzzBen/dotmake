#ifndef SHELL_TASK_H
#define SHELL_TASK_H

/**
 * @file shell_task.h
 * @brief ShellTask class
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/system_caller.h"
#include "src/task.h"

namespace dotmake {
/**
 * @class ShellTask
 *
 * @brief A task that runs shell commands
 */
class ShellTask : public Task {
 private:
  std::vector<std::string> commands;
  AbstractSystemCaller& system_caller;

 public:
  ShellTask(const ShellTask& shell_task,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());
  ShellTask(std::string name, std::vector<std::string> commands,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());
  ShellTask(std::string name, std::vector<std::string> commands,
            std::vector<std::string> required_task_names,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());

  virtual ~ShellTask() = default;

  virtual auto run() -> bool override;
};

}  // namespace dotmake
#endif  //  SHELL_TASK_H
