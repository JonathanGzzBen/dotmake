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

#include "dotmake/abstract_yaml_parser.h"
#include "dotmake/shell_task.h"
#include "dotmake/task.h"
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
  std::string name_;

 public:
  explicit ShellTaskParser(std::string name);
  ~ShellTaskParser() override;

  auto ParseString(std::string str) -> ShellTask override;

  auto ParseFile(std::string filename) -> ShellTask override;

  auto ParseNode(const YAML::Node& node) -> ShellTask override;
};

}  // namespace dotmake
#endif  //  SHELL_TASK_PARSER_H
