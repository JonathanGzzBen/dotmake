#ifndef LINK_TASK_H
#define LINK_TASK_H

/**
 * @file link_task.h
 * @brief LinkTask class
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "system_caller.h"
#include "task.h"

namespace dotmake {
/**
 * @class LinkTask
 *
 * @brief A task that creates symbolic links
 */
class LinkTask : public Task {
 private:
  std::vector<std::pair<std::string, std::string>> links;
  bool force;

  AbstractSystemCaller& system_caller;

 public:
  LinkTask(const LinkTask& link_task, AbstractSystemCaller& abstract_system_caller =
                                    SystemCaller::GetInstance());
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links, bool force,
           SystemCaller& system_caller = SystemCaller::GetInstance());

  virtual ~LinkTask() = default;

  virtual bool run() override;
};

}  // namespace dotmake
#endif  //  LINK_TASK_H
