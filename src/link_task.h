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

/**
 * @class LinkTask
 *
 * @brief A task that creates symbolic links
 */
class LinkTask : public Task {
 private:
  std::vector<std::pair<std::string, std::string>> links;
  bool force;

 public:
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links, bool force)
      : Task{name}, links{links}, force{force} {}
  virtual ~LinkTask() = default;

  virtual bool run() override {
    for (const auto& link : links) {
      if (SystemCaller::GetInstance().CreateSymbolicLink(link.first,
                                                         link.second)) {
        std::cout << "Error creating link \"" << link.first << "\"\n";
        return false;
      }
    }
    return true;
  }
};
#endif  //  LINK_TASK_H
