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

#include "src/abstract_yaml_parser.h"
#include "src/link_task.h"
#include "src/shell_task.h"
#include "src/task.h"
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
  std::string name;

  std::string str_toupper(std::string str) const;

 public:
  explicit LinkTaskParser(std::string name);
  ~LinkTaskParser() override;

  LinkTask parse_string(std::string str) override;

  LinkTask parse_file(std::string filename) override;

  LinkTask parse_node(const YAML::Node& node) override;
};

}  // namespace dotmake
#endif  //  LINK_TASK_PARSER_H
