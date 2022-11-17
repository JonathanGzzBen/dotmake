#include "shell_task.h"

dotmake::ShellTask::ShellTask(ShellTask& shell_task,
                              AbstractSystemCaller& system_caller)
    : Task{shell_task.name},
      commands{shell_task.commands},
      system_caller{system_caller} {}
dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              AbstractSystemCaller& system_caller)
    : Task{name}, commands{commands}, system_caller{system_caller} {}
dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              std::vector<std::string> required_task_names,
                              AbstractSystemCaller& system_caller)
    : Task{name, required_task_names},
      commands{commands},
      system_caller{system_caller} {}

bool dotmake::ShellTask::run() {
  for (const auto& command : commands) {
    if (system_caller.RunShellCommand(command)) {
      std::cout << "Error in command: " << command << "\n";
      return false;
    }
  }
  return true;
}
