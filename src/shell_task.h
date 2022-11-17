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
  ShellTask(ShellTask& shell_task,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{shell_task.name},
        commands{shell_task.commands},
        system_caller{system_caller} {}
  ShellTask(std::string name, std::vector<std::string> commands,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{name}, commands{commands}, system_caller{system_caller} {}
  ShellTask(std::string name, std::vector<std::string> commands,
            std::vector<std::string> required_task_names,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{name, required_task_names},
        commands{commands},
        system_caller{system_caller} {}

  virtual ~ShellTask() = default;

  virtual bool run() override {
    for (const auto& command : commands) {
      if (system_caller.RunShellCommand(command)) {
        std::cout << "Error in command: " << command << "\n";
        return false;
      }
    }
    return true;
  }
};

}  // namespace dotmake
#endif  //  SHELL_TASK_H
