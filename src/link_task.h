#ifndef LINK_TASK_H
#define LINK_TASK_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "src/task.h"

class LinkTask : public Task {
 private:
  std::vector<std::pair<std::string, std::string>> links;

 public:
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links)
      : Task{name}, links{links} {}
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links,
           std::vector<std::shared_ptr<Task>> requirements)
      : Task{name, requirements}, links{links} {}
  virtual ~LinkTask() = default;

  virtual bool run() override {
    this->run_requirements();
    for (const auto& link : links) {
        std::cout << "ln -sv " << link.first << " " << link.second << "\n";
      //if (std::system(command.c_str())) {
        //std::cout << "Error in command: " << command << "\n";
        //return false;
      //}
    }
    return true;
  }
};
#endif  //  LINK_TASK_H
