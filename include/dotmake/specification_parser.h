#ifndef SPECIFICATION_PARSER_H
#define SPECIFICATION_PARSER_H

/**
 * @file specification_parser.h
 * @brief SpecificationParser class
 */

#include <map>
#include <memory>
#include <string>

#include "dotmake/link_task.h"
#include "dotmake/link_task_parser.h"
#include "dotmake/shell_task.h"
#include "dotmake/shell_task_parser.h"
#include "dotmake/specification.h"
#include "dotmake/task.h"
#include "yaml-cpp/yaml.h"

namespace dotmake {
/**
 * @class SpecificationParser
 * @brief YamlParser for Specification
 */
class SpecificationParser : public AbstractYamlParser<Specification> {
 private:
  std::map<std::string, Task*> tasks_;

 public:
  SpecificationParser() = default;
  ~SpecificationParser() override = default;

  auto ParseString(std::string str) -> Specification override {
    return ParseNode(YAML::Load(str.c_str()));
  }

  auto ParseFile(std::string filename) -> Specification override {
    return ParseNode(YAML::LoadFile(filename));
  }

  auto ParseNode(const YAML::Node& node) -> Specification override {
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
              specification.tasks_[task_name] = std::make_shared<ShellTask>(
                  ShellTaskParser{task_name}.ParseNode(value));
            } else if (task_type == "link") {
              specification.tasks_[task_name] = std::make_shared<LinkTask>(
                  LinkTaskParser{task_name}.ParseNode(value));
            }
          }
        }
      }
    }
    return specification;
  }
};

}  // namespace dotmake

#endif  // SPECIFICATION_PARSER_H
