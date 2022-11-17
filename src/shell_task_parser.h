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

#include "src/shell_task.h"
#include "src/task.h"
#include "src/yaml-parser.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h"

namespace dotmake {
/**
 * @class ShellTaskParser
 *
 * @brief YamlParser implementation for ShellTask
 */
class ShellTaskParser : public YamlParser<ShellTask> {
 private:
  std::string name;

 public:
  explicit ShellTaskParser(std::string name) : name{name} {}
  ~ShellTaskParser() override = default;

  ShellTask parse_string(std::string str) override {
    return parse_node(YAML::Load(str.c_str()));
  }

  ShellTask parse_file(std::string filename) override {
    return parse_node(YAML::LoadFile(filename));
  }

  ShellTask parse_node(const YAML::Node& node) override {
    std::vector<std::string> commands;
    std::vector<std::string> required_task_names;
    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
      const auto key = it->first;
      const auto value = it->second;

      if (key.as<std::string>() == "commands" && value.IsSequence()) {
        for (const auto& command : value) {
          commands.emplace_back(command.as<std::string>());
        }
      } else if (key.as<std::string>() == "requires" && value.IsSequence()) {
        for (const auto& task_name : value) {
          required_task_names.push_back(task_name.as<std::string>());
        }
      }
    }
    if (commands.size() == 0) {
      throw std::runtime_error{"Shell task \"" + name + "\" has no commands"};
    }
    return ShellTask{name, commands, required_task_names};
  }
};

}  // namespace dotmake
#endif  //  SHELL_TASK_PARSER_H
