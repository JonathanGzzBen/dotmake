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

template <typename T>
class YamlParser {
 public:
  virtual ~YamlParser() = default;
  virtual T parse_file(std::string filename) = 0;
  virtual T parse_node(const YAML::Node& node) = 0;
};
#endif  //  TASK_PARSER_H
