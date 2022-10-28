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

#include "src/task.h"

/**
 * @class ShellTask
 *
 * @brief A task that runs shell commands
 */
class ShellTask : public Task {
 private:
  std::vector<std::string> commands;

 public:
  ShellTask(std::string name, std::vector<std::string> commands)
      : Task{name}, commands{commands} {}
  ShellTask(std::string name, std::vector<std::string> commands,
            std::vector<std::string> required_task_names)
      : Task{name, required_task_names}, commands{commands} {}

  virtual ~ShellTask() = default;

  virtual bool run() override {
    std::cout << "Running task ====>" << get_name() << "\n";
    for (const auto& command : commands) {
      std::cout << command << "\n";
      // #ifdef WIN32
      //       if (std::system(std::string("powershell " + command).c_str())) {
      // #else
      //       if (std::system(command.c_str())) {
      // #endif
      //         std::cout << "Error in command: " << command << "\n";
      //         return false;
      //       }
    }
    return true;
  }
};
#endif  //  SHELL_TASK_H
