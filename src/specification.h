#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <map>
#include <memory>
#include <string>

#include "src/task.h"

class Specification {
  friend class SpecificationParser;

 private:
  std::map<std::string, std::shared_ptr<Task>> tasks;

 public:
  Specification() = default;

  [[nodiscard]] bool run(const std::string& task_name) const {
    if (tasks.find(task_name) == tasks.cend()) {
      std::cout << "There is no task with name \"" << task_name
                << "\"  in specification file\n";
      return false;
    }
    tasks.at(task_name)->run(tasks);
    return true;
  }
};

#endif  // SPECIFICATION_H
