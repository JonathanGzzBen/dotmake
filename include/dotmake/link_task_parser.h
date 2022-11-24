#ifndef LINK_TASK_PARSER_H
#define LINK_TASK_PARSER_H

/**
 * @file link_task_parser.h
 * @brief LinkTaskParser class
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "dotmake/abstract_yaml_parser.h"
#include "dotmake/link_task.h"
#include "dotmake/shell_task.h"
#include "dotmake/task.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace dotmake {
/**
 * @class LinkTaskParser
 * @brief YamlParser implementation for LinkTask
 */
class LinkTaskParser : public AbstractYamlParser<LinkTask> {
 private:
  std::string name_;

  static auto StrToupper(std::string str) -> std::string;

 public:
  explicit LinkTaskParser(std::string name);
  ~LinkTaskParser() override;

  auto ParseString(std::string str) -> LinkTask override;

  auto ParseFile(std::string filename) -> LinkTask override;

  auto ParseNode(const YAML::Node& node) -> LinkTask override;
};

}  // namespace dotmake
#endif  //  LINK_TASK_PARSER_H
