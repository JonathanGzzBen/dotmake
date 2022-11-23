#include "dotmake/link_task_parser.h"

dotmake::LinkTaskParser::LinkTaskParser(std::string name)
    : name{std::move(name)} {}
dotmake::LinkTaskParser::~LinkTaskParser() = default;

auto dotmake::LinkTaskParser::str_toupper(std::string str) -> std::string {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return str;
}

inline auto dotmake::LinkTaskParser::parse_string(std::string str)
    -> dotmake::LinkTask {
  return parse_node(YAML::Load(str.c_str()));
}

inline auto dotmake::LinkTaskParser::parse_file(std::string filename)
    -> dotmake::LinkTask {
  return parse_node(YAML::LoadFile(filename));
}

auto dotmake::LinkTaskParser::parse_node(const YAML::Node& node)
    -> dotmake::LinkTask {
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
  if (links.empty()) {
    throw std::runtime_error{"Link task \"" + name + "\" has no links"};
  }
  return LinkTask{name, links, force};
}
