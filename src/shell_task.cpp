#include "shell_task.h"

dotmake::ShellTask::ShellTask(const ShellTask& shell_task,
                              AbstractSystemCaller& system_caller)
    : Task{shell_task.name},
      commands{shell_task.commands},
      system_caller{system_caller} {}

dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              AbstractSystemCaller& system_caller)
    : Task{std::move(name)},
      commands{std::move(commands)},
      system_caller{system_caller} {}

dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              std::vector<std::string> required_task_names,
                              AbstractSystemCaller& system_caller)
    : Task{std::move(name), std::move(required_task_names)},
      commands{std::move(commands)},
      system_caller{system_caller} {}

auto dotmake::ShellTask::run() -> bool {
  for (const auto& command : commands) {
    if (system_caller.RunShellCommand(command) != 0) {
      std::cout << "Error in command: " << command << "\n";
      return false;
    }
  }
  return true;
}
