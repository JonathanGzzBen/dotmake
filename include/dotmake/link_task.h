#ifndef LINK_TASK_H
#define LINK_TASK_H

/**
 * @file link_task.h
 * @brief LinkTask class
 */

#include <string>
#include <vector>

#include "dotmake/system_caller.h"
#include "dotmake/task.h"

namespace dotmake {
/**
 * @class LinkTask
 *
 * @brief A task that creates symbolic links
 */
class LinkTask : public Task {
 private:
  std::vector<std::pair<std::string, std::string>> links_;
  bool force_;

  AbstractSystemCaller& system_caller_;

 public:
  LinkTask(const LinkTask& link_task,
           AbstractSystemCaller& abstract_system_caller =
               SystemCaller::GetInstance());
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links, bool force,
           std::string help_message,
           SystemCaller& system_caller = SystemCaller::GetInstance());

  ~LinkTask() override = default;

  auto Run() -> bool override;
};

}  // namespace dotmake
#endif  //  LINK_TASK_H
