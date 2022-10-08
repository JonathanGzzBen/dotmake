#ifndef SHELL_TASK_H
#define SHELL_TASK_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/task.h"

class ShellTask : public Task {
 private:
  std::vector<std::string> commands;

 public:
  ShellTask(std::string name, std::vector<std::string> commands)
      : Task{name}, commands{commands} {}
  ShellTask(std::string name, std::vector<std::shared_ptr<Task>> requirements)
      : Task{name, requirements} {}
  virtual ~ShellTask() = default;

  virtual bool run() override {
    this->run_requirements();
    for (const auto& command : commands) {
#ifdef WIN32
      if (std::system(std::string("powershell " + command).c_str())) {
#else
      if (std::system(command.c_str())) {
#endif
        std::cout << "Error in command: " << command << "\n";
        return false;
      }
    }
    return true;
  }
};
#endif  //  SHELL_TASK_H
