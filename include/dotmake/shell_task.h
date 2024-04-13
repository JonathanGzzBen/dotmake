#ifndef SHELL_TASK_H
#define SHELL_TASK_H

/**
 * @file shell_task.h
 * @brief ShellTask class
 */

#include <string>
#include <vector>

#include "dotmake/system_caller.h"
#include "dotmake/task.h"

namespace dotmake {
/**
 * @class ShellTask
 *
 * @brief A task that runs shell commands
 */
class ShellTask : public Task {
 private:
  std::vector<std::string> commands_;
  AbstractSystemCaller& system_caller_;

 public:
  explicit ShellTask(
      AbstractSystemCaller& system_caller = SystemCaller::GetInstance());
  ShellTask(const ShellTask& shell_task,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());
  ShellTask(std::string name, std::vector<std::string> commands,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());
  ShellTask(std::string name, std::vector<std::string> commands,
            std::vector<std::string> required_task_names,
            AbstractSystemCaller& system_caller = SystemCaller::GetInstance());

  ~ShellTask() override = default;

  auto Run() -> bool override;
};

}  // namespace dotmake
#endif  //  SHELL_TASK_H
