#ifndef TASK_PARSER_H
#define TASK_PARSER_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/shell_task.h"
#include "src/task.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

class TaskParser {
 public:
  virtual ~TaskParser() = default;
  virtual ShellTask parse_file(std::string filename) = 0;
  virtual ShellTask parse_string(std::string string) = 0;
};
#endif  //  TASK_PARSER_H
