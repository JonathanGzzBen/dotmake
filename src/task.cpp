#include "dotmake/task.h"

dotmake::Task::Task(std::string name) : name_{std::move(name)} {};
dotmake::Task::Task(std::string name, std::string help_message)
    : name_{std::move(name)}, help_message_(std::move(help_message)){};
dotmake::Task::Task(std::string name, std::string help_message,
                    std::vector<std::string> required_task_names)
    : name_{std::move(name)},
      help_message_(std::move(help_message)),
      required_task_names_{std::move(required_task_names)} {};

dotmake::Task::~Task() = default;

inline auto dotmake::Task::GetName() const -> std::string { return name_; }

auto dotmake::Task::SetName(const std::string& name) -> Task& {
  name_ = name;
  return *this;
}

/**
 * @brief Gets the name of the task
 * @return name of task
 */
[[nodiscard]] auto dotmake::Task::GetHelpMessage() const -> std::string {
  return help_message_;
}
/**
 * @brief Gets the help message of the task
 * @return help message of task
 */
auto dotmake::Task::SetHelpMessage(const std::string& help_mesage) -> Task& {
  help_message_ = help_mesage;
  return *this;
}
