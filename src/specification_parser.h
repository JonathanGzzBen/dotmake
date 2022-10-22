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

class SpecificationParser : public YamlParser<Specification> {
 private:
  std::map<std::string, Task*> tasks;

 public:
  SpecificationParser() = default;
  ~SpecificationParser() override = default;

  Specification parse_file(std::string filename) override {
    return parse_node(YAML::LoadFile(filename));
  }

  Specification parse_node(const YAML::Node& node) override {
    Specification specification{};
    for (const auto object : node) {
      const auto key = object.first;
      const auto value = object.second;

      if (value.IsMap()) {
        for (const auto sub_object : value) {
          const auto sub_key = sub_object.first;
          const auto sub_value = sub_object.second;
          // If it is a task
          if (sub_key.as<std::string>() == "type") {
            const auto task_type = sub_value.as<std::string>();
            const auto task_name = key.as<std::string>();
            if (task_type == "shell") {
              specification.tasks[task_name] = std::make_shared<ShellTask>(
                  ShellTaskParser{task_name}.parse_node(value));
            } else if (task_type == "link") {
              specification.tasks[task_name] = std::make_shared<LinkTask>(
                  LinkTaskParser{task_name}.parse_node(value));
            }
          }
        }
      }
    }
    return specification;
  }
};

#endif  // SPECIFICATION_PARSER_H
