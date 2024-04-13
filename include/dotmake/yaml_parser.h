#pragma once
/**
 * @file yaml-parser.h
 * @brief YamlParser class
 */

#include <string>

#include "dotmake/link_task.h"
#include "dotmake/shell_task.h"
#include "dotmake/specification.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/yaml.h" // This must be included to initialize some templates

/**
 * @brief Yaml Parser
 * @tparam T type that should be parsed
 */
namespace dotmake::yaml_parser {

/**
 * @brief parses a node
 * @param node YAML node to parse
 * @return Object parsed from YAML node
 */
template <typename T>
auto ParseNode(YAML::Node node) -> T {
  static_assert(std::is_same<T, ShellTask>::value ||
                    std::is_same<T, ShellTask>::value ||
                    std::is_same<T, Specification>::value,
                "No yaml parser implemented for this type");
}

/**
 * @brief parses a string
 * @param filename yaml string to parse
 * @return Object parsed from string
 */
template <typename T>
auto ParseString(const std::string& str) -> T {
  return ParseNode<T>(YAML::Load(str));
}

/**
 * @brief parses a file
 * @param filename filename of file to parse
 * @return Object parsed from file
 */
template <typename T>
auto ParseFile(const std::string& filename) -> T {
  return ParseNode<T>(YAML::LoadFile(filename));
}

template <>
auto ParseNode<ShellTask>(YAML::Node node) -> ShellTask;
template <>
auto ParseNode<LinkTask>(YAML::Node node) -> LinkTask;
template <>
auto ParseNode<Specification>(YAML::Node node) -> Specification;

}  // namespace dotmake::yaml_parser
