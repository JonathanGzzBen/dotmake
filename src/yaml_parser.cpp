#include "dotmake/yaml_parser.h"

#include <algorithm>
#include <string>
#include <vector>

#include "dotmake/link_task.h"
#include "dotmake/shell_task.h"
#include "dotmake/specification.h"
#include "yaml-cpp/node/node.h"

namespace dotmake::yaml_parser {

template <>
auto ParseNode<ShellTask>(YAML::Node node) -> ShellTask {
  std::vector<std::string> commands;
  std::vector<std::string> required_task_names;
  auto commands_nodes = node["commands"];
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
  if (commands.empty()) {
    throw std::runtime_error{"Shell task has no commands "};
  }
  return ShellTask{"default", commands, required_task_names};
}
template <>
auto ParseNode<LinkTask>(YAML::Node node) -> LinkTask {
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
      auto value_str = value.as<std::string>();
      std::transform(
          value_str.begin(), value_str.end(), value_str.begin(),
          [](unsigned char character) { return std::toupper(character); });
      force = (value_str == "TRUE");
    }
  }
  if (links.empty()) {
    throw std::runtime_error{"Link task has no links"};
  }
  return LinkTask{"default", links, force};
}

template <>
auto ParseNode<Specification>(YAML::Node node) -> Specification {
  Specification specification{};
  for (const auto object : node) {
    const auto key = object.first;
    const auto value = object.second;

    if (value.IsMap()) {
      const auto name = key.as<std::string>();
      const auto type = value["type"].as<std::string>();
      if (type == "shell") {
        specification.GetTasks()->insert(
            {name, std::make_shared<ShellTask>(
                       yaml_parser::ParseNode<ShellTask>(value))});
      } else if (type == "link") {
        specification.GetTasks()->insert(
            {name, std::make_shared<LinkTask>(
                       yaml_parser::ParseNode<LinkTask>(value))});
      } else {
        break;
      }
      specification.GetTasks()->at(name)->SetName(name);
    }
  }
  return specification;
}

}  // namespace dotmake::yaml_parser
