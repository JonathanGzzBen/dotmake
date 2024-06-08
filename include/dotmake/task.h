#ifndef TASK_H
#define TASK_H

/**
 * @file task.h
 * @brief Task abstract class
 */

#include <string>
#include <vector>

namespace dotmake {
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
  std::string name_;
  std::vector<std::string> required_task_names_;
  std::string help_message_;

  explicit Task(std::string name);
  explicit Task(std::string name, std::string help_message);
  Task(std::string name, std::string help_message,
       std::vector<std::string> required_task_names);

 public:
  virtual ~Task();

  /**
   * @brief Runs task
   * @retval true if task was sun successfully
   * @retval false if task failed
   */
  [[nodiscard]] virtual auto Run() -> bool = 0;

  /**
   * @brief Gets the name of the task
   * @return name of task
   */
  [[nodiscard]] virtual auto GetName() const -> std::string;
  /**
   * @brief Gets the name of the task
   * @return name of task
   */
  virtual auto SetName(const std::string& name) -> Task&;
  /**
   * @brief Gets the name of the task
   * @return name of task
   */
  [[nodiscard]] virtual auto GetHelpMessage() const -> std::string;
  /**
   * @brief Gets the help message of the task
   * @return help message of task
   */
  virtual auto SetHelpMessage(const std::string& help_mesage) -> Task&;
};
}  // namespace dotmake

#endif  //  TASK_H
