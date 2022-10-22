#ifndef TASK_H
#define TASK_H

/**
 * @file task.h
 * @brief Task abstract class
 */

#include <map>
#include <memory>
#include <string>
#include <vector>

/**
 * @class Task
 * @brief A runnable task
 *
 * A task can be of one of the following types: shell, link.
 *
 * It can be run either individually (without verifying dependencies) or using
 * an Specification class which can manage dependencies.
 *
 */
class Task {
  friend class Specification;

 protected:
  std::vector<std::string> required_task_names;
  std::string name;

  Task(std::string name) : name{name} {};
  Task(std::string name, std::vector<std::string> required_task_names)
      : name{name}, required_task_names{required_task_names} {};

 public:
  virtual ~Task() = default;

  /**
   * @brief Runs task
   * @retval true if task was sun successfully
   * @retval false if task failed
   */
  [[nodiscard]] virtual bool run() = 0;

  /**
   * @brief Gets the name of the task
   * @return name of task
   */
  virtual inline std::string get_name() { return name; }
};
#endif  //  TASK_H
