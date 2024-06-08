#include "dotmake/shell_task.h"

#include <iostream>

dotmake::ShellTask::ShellTask(const ShellTask& shell_task,
                              AbstractSystemCaller& system_caller)
    : Task{shell_task.name_, shell_task.help_message_,
           shell_task.required_task_names_},
      commands_{shell_task.commands_},
      system_caller_{system_caller} {}

dotmake::ShellTask::ShellTask(AbstractSystemCaller& system_caller)
    : Task(""), system_caller_{system_caller} {}

dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              AbstractSystemCaller& system_caller)
    : Task{std::move(name)},
      commands_{std::move(commands)},
      system_caller_{system_caller} {}

dotmake::ShellTask::ShellTask(std::string name,
                              std::vector<std::string> commands,
                              std::string help_message,
                              std::vector<std::string> required_task_names,
                              AbstractSystemCaller& system_caller)
    : Task{std::move(name), std::move(help_message),
           std::move(required_task_names)},
      commands_{std::move(commands)},
      system_caller_{system_caller} {}

auto dotmake::ShellTask::Run() -> bool {
  for (const auto& command : commands_) {
    if (system_caller_.RunShellCommand(command) != 0) {
      std::cout << "Error in command: " << command << "\n";
      return false;
    }
  }
  return true;
}
