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

#include "src/system_caller.h"
#include "src/task.h"

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
  LinkTask(LinkTask& link_task, AbstractSystemCaller& abstract_system_caller =
                                    SystemCaller::GetInstance())
      : Task{link_task.name},
        links{link_task.links},
        force{link_task.force},
        system_caller{abstract_system_caller} {}
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links, bool force,
           SystemCaller& system_caller = SystemCaller::GetInstance())
      : Task{name}, links{links}, force{force}, system_caller{system_caller} {}

  virtual ~LinkTask() = default;

  virtual bool run() override {
    for (const auto& link : links) {
      if (system_caller.CreateSymbolicLink(link.first, link.second)) {
        std::cout << "Error creating link \"" << link.first << "\"\n";
        return false;
      }
    }
    return true;
  }
};

}  // namespace dotmake
#endif  //  LINK_TASK_H
