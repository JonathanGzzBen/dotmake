#ifndef SPECIFICATION_PARSER_H
#define SPECIFICATION_PARSER_H

#include <map>
#include <memory>
#include <string>

#include "src/link_task.h"
#include "src/link_task_parser.h"
#include "src/shell_task.h"
#include "src/shell_task_parser.h"
#include "src/specification.h"
#include "src/task.h"
#include "yaml-cpp/yaml.h"

class SpecificationParser {
 private:
  std::map<std::string, Task*> tasks;

 public:
  SpecificationParser() = default;

  Specification parse_file(const std::string& filename) {
    Specification specification{};

    const auto specification_file = YAML::LoadFile(filename);

    for (const auto object : specification_file) {
      const auto key = object.first;
      const auto value = object.second;

      if (value.IsMap()) {
        for (const auto sub_object : value) {
          const auto sub_key = sub_object.first;
          const auto sub_value = sub_object.second;

          if (sub_key.as<std::string>() == "type" &&
              sub_value.as<std::string>() == "shell") {
            specification.push_task(std::make_shared<ShellTask>(
                ShellTaskParser{key.as<std::string>()}.parse_node(value)));
          }
          else if (sub_key.as<std::string>() == "type" &&
              sub_value.as<std::string>() == "link") {
            specification.push_task(std::make_shared<LinkTask>(
                LinkTaskParser{key.as<std::string>()}.parse_node(value)));
          }
        }
      }
    }

    return specification;
  }
};

#endif  // SPECIFICATION_PARSER_H
