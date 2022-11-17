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

#include "src/link_task.h"
#include "src/shell_task.h"
#include "src/task.h"
#include "src/yaml-parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace dotmake {
/**
 * @class LinkTaskParser
 * @brief YamlParser implementation for LinkTask
 */
class LinkTaskParser : public YamlParser<LinkTask> {
 private:
  std::string name;

  std::string str_toupper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return str;
  }

 public:
  explicit LinkTaskParser(std::string name) : name{name} {}
  ~LinkTaskParser() override = default;

  LinkTask parse_string(std::string str) override {
    return parse_node(YAML::Load(str.c_str()));
  }

  LinkTask parse_file(std::string filename) override {
    return parse_node(YAML::LoadFile(filename));
  }

  LinkTask parse_node(const YAML::Node& node) override {
    std::vector<std::pair<std::string, std::string>> links;
    bool force = false;
    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
      const auto key = it->first;
      const auto value = it->second;

      if (key.as<std::string>() == "links" && value.IsMap()) {
        for (const auto& link : value) {
          links.emplace_back(link.first.as<std::string>(),
                             link.second.as<std::string>());
        }
      } else if (key.as<std::string>() == "force" && value.IsScalar()) {
        force = str_toupper(value.as<std::string>()) == "TRUE";
      }
    }
    if (links.size() == 0) {
      throw std::runtime_error{"Link task \"" + name + "\" has no links"};
    }
    return LinkTask{name, links, force};
  }
};

}  // namespace dotmake
#endif  //  LINK_TASK_PARSER_H
