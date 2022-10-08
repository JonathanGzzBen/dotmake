#ifndef TASK_H
#define TASK_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Task {
 protected:
  std::vector<std::string> required_task_names;
  std::string name;

  Task(std::string name) : name{name} {};
  Task(std::string name, std::vector<std::string> required_task_names)
      : name{name}, required_task_names{required_task_names} {};

  bool run_requirements(std::map<std::string, std::shared_ptr<Task>> tasks) {
    for (const auto& task_name : required_task_names) {
      if (!tasks.find(task_name)->second->run(tasks)) {
        return false;
      }
    }
    return true;
  }

 public:
  virtual ~Task() = default;

  virtual bool run(std::map<std::string, std::shared_ptr<Task>> tasks) = 0;

  virtual inline std::string get_name() { return name; }
};
#endif  //  TASK_H
