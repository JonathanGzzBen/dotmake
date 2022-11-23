#include "shell_task_parser.h"

#include "shell_task.h"

dotmake::ShellTaskParser::ShellTaskParser(std::string name)
    : name{std::move(name)} {}
dotmake::ShellTaskParser::~ShellTaskParser() = default;

inline auto dotmake::ShellTaskParser::parse_string(std::string str)
    -> dotmake::ShellTask {
  return parse_node(YAML::Load(str.c_str()));
}

inline auto dotmake::ShellTaskParser::parse_file(std::string filename)
    -> dotmake::ShellTask {
  return parse_node(YAML::LoadFile(filename));
}

auto dotmake::ShellTaskParser::parse_node(const YAML::Node& node)
    -> dotmake::ShellTask {
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
  if (commands.empty()) {
    throw std::runtime_error{"Shell task \"" + name + "\" has no commands"};
  }
  return ShellTask{name, commands, required_task_names};
}
