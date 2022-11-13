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

/**
 * @class ShellTask
 *
 * @brief A task that runs shell commands
 */
class ShellTask : public Task {
 private:
  std::vector<std::string> commands;
  SystemCaller& system_caller;

 public:
  ShellTask(std::string name, std::vector<std::string> commands,
            SystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{name}, commands{commands}, system_caller{system_caller} {}
  ShellTask(std::string name, std::vector<std::string> commands,
            std::vector<std::string> required_task_names,
            SystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{name, required_task_names},
        commands{commands},
        system_caller{system_caller} {}

  virtual ~ShellTask() = default;

  virtual bool run() override {
    for (const auto& command : commands) {
      if (system_caller.RunShellCommand(command.c_str())) {
        std::cout << "Error in command: " << command << "\n";
        return false;
      }
    }
    return true;
  }

  virtual std::vector<std::string> get_commands() const { return commands; }
};
#endif  //  SHELL_TASK_H
