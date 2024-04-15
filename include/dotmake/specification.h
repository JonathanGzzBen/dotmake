#ifndef SPECIFICATION_H
#define SPECIFICATION_H

/**
 * @file specification.h
 * @brief Specification class
 */

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>

#include "dotmake/task.h"

namespace dotmake {
/**
 * @brief Holds data of tasks specified in one or more specification files.
 *
 * Used to run an specific task and ensuring its dependencies are executed in
 * order.
 */
class Specification {
  friend class SpecificationParser;

 private:
  std::map<std::string, std::shared_ptr<Task>> tasks_;

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
  static auto RecursiveTasksFill(
      const std::string& task_name,
      std::map<std::string, std::shared_ptr<Task>> tasks,
      std::set<std::string>& processed_tasks,
      std::queue<std::string>& result_queued_tasks) -> bool;

 public:
  Specification();

  /**
   * @brief Runs specified task and its requirements, which should be available
   * in the specification.
   * @param task_name Name of task to run
   * @return Whether the task was run successfully or not
   */
  [[nodiscard]] auto Run(const std::string& task_name) const -> bool;
  /**
   * @brief Prints to stdout the help message for specified task, which sould be
   * available in the specification.
   * @param task_name Name of task to print message
   * @return Whether the task message was printed successfully or not
   */
  [[nodiscard]] auto PrintHelpMessageForTask(const std::string& task_name) const
      -> bool;
  [[nodiscard]] auto GetTasks() -> auto { return &tasks_; }
};
}  // namespace dotmake
#endif  // SPECIFICATION_H
