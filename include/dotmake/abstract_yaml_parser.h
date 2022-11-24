#ifndef TASK_PARSER_H
#define TASK_PARSER_H

/**
 * @file yaml-parser.h
 * @brief YamlParser class
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "dotmake/shell_task.h"
#include "dotmake/task.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

/**
 * @brief Yaml Parser
 * @tparam T type that should be parsed
 */
template <typename T>
class AbstractYamlParser {
 public:
  virtual ~AbstractYamlParser() = default;

  /**
   * @brief parses a string
   * @param filename yaml string to parse
   * @return Object parsed from string
   */
  virtual auto ParseString(std::string str) -> T = 0;

  /**
   * @brief parses a file
   * @param filename filename of file to parse
   * @return Object parsed from file
   */
  virtual auto ParseFile(std::string filename) -> T = 0;

  /**
   * @brief parses a file
   * @param node YAML node to parse
   * @return Object parsed from YAML node
   */
  virtual auto ParseNode(const YAML::Node& node) -> T = 0;
};
#endif  //  TASK_PARSER_H
