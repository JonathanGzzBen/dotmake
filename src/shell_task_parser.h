#ifndef SHELL_TASK_PARSER_H
#define SHELL_TASK_PARSER_H

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

/**
 * @class ShellTaskParser
 *
 * @brief YamlParser for ShellTask
 */
class ShellTaskParser : public YamlParser<ShellTask> {
 private:
  std::string name;

 public:
  explicit ShellTaskParser(std::string name) : name{name} {}
  ~ShellTaskParser() override = default;

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
    return ShellTask{name, commands, required_task_names};
  }
};
#endif  //  SHELL_TASK_PARSER_H
