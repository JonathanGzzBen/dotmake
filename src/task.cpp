#include "task.h"

dotmake::Task::Task(std::string name) : name{name} {};
dotmake::Task::Task(std::string name,
                    std::vector<std::string> required_task_names)
    : name{name}, required_task_names{required_task_names} {};

dotmake::Task::~Task() = default;

inline std::string dotmake::Task::get_name() const { return name; }
