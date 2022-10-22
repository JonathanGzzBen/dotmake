#ifndef SPECIFICATION_H
#define SPECIFICATION_H

/**
 * @file specification.h
 * @brief Specification class
 */

#include <map>
#include <memory>
#include <stack>
#include <string>

#include "src/task.h"

/**
 * @brief Holds data of tasks specified in one or more specification files.
 *
 * Used to run an specific task and ensuring its dependencies are executed in
 * order.
 */
class Specification {
  friend class SpecificationParser;

 private:
  std::map<std::string, std::shared_ptr<Task>> tasks;

  /**
   * @brief Does a postorder sort for the dependencies tree needed to run task
   * with task_name and stores them in result_sorted_tasks
   * @param task_name Name of task to run
   * @param tasks map of all tasks in specification
   * @param processed_tasks set of tasks already processed and
   * sorted in result_sorted_tasks
   * @param result_sorted_tasks stack of tasks sorted in order
   * to run task with task_name
   * @retval true if tasks could be sorted successfully
   * @retval false if sorting failed (cyclic o missing dependencies)
   */
  static bool recursive_tasks_fill(
      const std::string& task_name,
      const std::map<std::string, std::shared_ptr<Task>> tasks,
      std::set<std::string>& processed_tasks,
      std::stack<std::string>& result_sorted_tasks) {
    if (processed_tasks.find(task_name) != processed_tasks.cend()) {
      // Cyclic dependency found
      std::cerr << "Cyclic dependency found in task \"" << task_name << "\"\n";
      return false;
    }
    result_sorted_tasks.push(task_name);
    processed_tasks.insert(task_name);
    for (const auto& required_task : tasks.at(task_name)->required_task_names) {
      if (!recursive_tasks_fill(required_task, tasks, processed_tasks,
                                result_sorted_tasks)) {
        return false;
      }
    }
    return true;
  }

 public:
  Specification() = default;

  /**
   * @brief Runs specified task and its requirements, which should be available
   * in the specification.
   * @param task_name Name of task to run
   * @return Whether the task was run successfully or not
   */
  [[nodiscard]] bool run(const std::string& task_name) const {
    if (tasks.find(task_name) == tasks.cend()) {
      std::cerr << "There is no task with name \"" << task_name
                << "\"  in specification file\n";
      return false;
    }

    std::stack<std::string> sorted_tasks;
    std::set<std::string> processed_tasks;
    if (!recursive_tasks_fill(task_name, tasks, processed_tasks,
                              sorted_tasks)) {
      return false;
    }
    while (!sorted_tasks.empty()) {
      if (!tasks.at(sorted_tasks.top())->run()) {
        return false;
      }
      sorted_tasks.pop();
    }

    return true;
  }
};

#endif  // SPECIFICATION_H
