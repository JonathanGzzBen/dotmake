#include "dotmake/task.h"

dotmake::Task::Task(std::string name) : name_{std::move(name)} {};
dotmake::Task::Task(std::string name,
                    std::vector<std::string> required_task_names)
    : name_{std::move(name)},
      required_task_names_{std::move(required_task_names)} {};

dotmake::Task::~Task() = default;

inline auto dotmake::Task::GetName() const -> std::string { return name_; }

auto dotmake::Task::SetName(const std::string& name) -> Task& {
  name_ = name;
  return *this;
}
