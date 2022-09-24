#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <map>
#include <memory>
#include <string>

#include "src/task.h"

class Specification {
 private:
  std::map<std::string, std::shared_ptr<Task>> tasks;

 public:
  Specification() = default;

  void push_task(std::shared_ptr<Task> task) { tasks[task->get_name()] = task; }

  inline std::map<std::string, std::shared_ptr<Task>> get_tasks() const {
    return tasks;
  }
};

#endif  // SPECIFICATION_H
