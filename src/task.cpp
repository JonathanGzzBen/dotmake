#include "task.h"

dotmake::Task::Task(std::string name) : name{std::move(name)} {};
dotmake::Task::Task(std::string name,
                    std::vector<std::string> required_task_names)
    : name{std::move(name)},
      required_task_names{std::move(required_task_names)} {};

dotmake::Task::~Task() = default;

inline auto dotmake::Task::get_name() const -> std::string { return name; }
