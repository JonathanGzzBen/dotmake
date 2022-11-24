#include "dotmake/link_task_parser.h"

dotmake::LinkTaskParser::LinkTaskParser(std::string name)
    : name_{std::move(name)} {}
dotmake::LinkTaskParser::~LinkTaskParser() = default;

auto dotmake::LinkTaskParser::StrToupper(std::string str) -> std::string {
  std::transform(
      str.begin(), str.end(), str.begin(),
      [](unsigned char character) { return std::toupper(character); });
  return str;
}

inline auto dotmake::LinkTaskParser::ParseString(std::string str)
    -> dotmake::LinkTask {
  return ParseNode(YAML::Load(str.c_str()));
}

inline auto dotmake::LinkTaskParser::ParseFile(std::string filename)
    -> dotmake::LinkTask {
  return ParseNode(YAML::LoadFile(filename));
}

auto dotmake::LinkTaskParser::ParseNode(const YAML::Node& node)
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
      force = StrToupper(value.as<std::string>()) == "TRUE";
    }
  }
  if (links.empty()) {
    throw std::runtime_error{"Link task \"" + name_ + "\" has no links"};
  }
  return LinkTask{name_, links, force};
}
