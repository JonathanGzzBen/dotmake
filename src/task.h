#ifndef TASK_H
#define TASK_H

#include <memory>
#include <string>
#include <vector>

class Task {
 protected:
  std::vector<std::shared_ptr<Task>> requirements;
  std::string name;

  Task(std::string name) : name{name} {};
  Task(std::string name, std::vector<std::shared_ptr<Task>> requirements)
      : name{name}, requirements{requirements} {};

  bool run_requirements() {
    for (const auto& task : requirements) {
      if (!task->run()) {
        return false;
      }
    }
    return true;
  }

 public:
  virtual ~Task() = default;

  virtual bool run() = 0;

  virtual inline std::string get_name() {
      return name;
  }
};
#endif  //  TASK_H
