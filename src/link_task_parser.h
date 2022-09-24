#ifndef LINK_TASK_PARSER_H
#define LINK_TASK_PARSER_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "src/link_task.h"
#include "src/shell_task.h"
#include "src/task.h"
#include "src/task_parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

class LinkTaskParser : public Parser<LinkTask> {
 private:
  std::string name;

 public:
  LinkTaskParser(std::string name) : name{name} {}
  virtual ~LinkTaskParser() = default;

  LinkTask parse_file(std::string filename) override {
    return parse_node(YAML::LoadFile(filename));
  }

  LinkTask parse_string(std::string string) override {
    return parse_node(YAML::Load(string));
  }

  LinkTask parse_node(const YAML::Node& node) {
    std::vector<std::pair<std::string, std::string>> links;
    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
      const auto key = it->first;
      const auto value = it->second;

      if (key.as<std::string>() == "links" && value.IsMap()) {
        for (const auto& link : value) {
          links.emplace_back(link.first.as<std::string>(),
                             link.second.as<std::string>());
        }
      }
    }
    return LinkTask{name, links};
  }
};
#endif  //  LINK_TASK_PARSER_H
