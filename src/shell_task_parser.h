#ifndef SHELL_TASK_PARSER_H
#define SHELL_TASK_PARSER_H

/**
 * @file shell_task_parser.h
 * @brief ShellTaskParser class
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "abstract_yaml_parser.h"
#include "shell_task.h"
#include "task.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace dotmake {
/**
 * @class ShellTaskParser
 *
 * @brief YamlParser implementation for ShellTask
 */
class ShellTaskParser : public AbstractYamlParser<ShellTask> {
 private:
  std::string name;

 public:
  explicit ShellTaskParser(std::string name);
  ~ShellTaskParser() override;

  auto parse_string(std::string str) -> ShellTask override;

  auto parse_file(std::string filename) -> ShellTask override;

  auto parse_node(const YAML::Node& node) -> ShellTask override;
};

}  // namespace dotmake
#endif  //  SHELL_TASK_PARSER_H
