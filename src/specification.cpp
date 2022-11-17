#include "specification.h"

dotmake::Specification::Specification() = default;

bool dotmake::Specification::recursive_tasks_fill(
    const std::string& task_name,
    const std::map<std::string, std::shared_ptr<Task>> tasks,
    std::set<std::string>& processed_tasks,
    std::queue<std::string>& result_queued_tasks) {
  processed_tasks.insert(task_name);
  for (const auto& required_task : tasks.at(task_name)->required_task_names) {
    if (processed_tasks.find(required_task) != processed_tasks.cend()) {
      // If required task was already processed
      continue;
    }
    if (!recursive_tasks_fill(required_task, tasks, processed_tasks,
                              result_queued_tasks)) {
      return false;
    }
  }
  result_queued_tasks.push(task_name);
  return true;
}

[[nodiscard]] bool dotmake::Specification::run(
    const std::string& task_name) const {
  if (tasks.find(task_name) == tasks.cend()) {
    std::cerr << "There is no task with name \"" << task_name
              << "\"  in specification file\n";
    return false;
  }

  std::queue<std::string> queued_tasks;
  std::set<std::string> processed_tasks;
  if (!recursive_tasks_fill(task_name, tasks, processed_tasks, queued_tasks)) {
    return false;
  }
  while (!queued_tasks.empty()) {
    if (!tasks.at(queued_tasks.front())->run()) {
      return false;
    }
    queued_tasks.pop();
  }

  return true;
}
