#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "dotmake/yaml_parser.h"

/**
 * @file main.cpp
 */

/**
 * @brief Handles help message
 * @param argc Argument count
 * @param argv Argument values
 * @retval true if help message was displayed
 * @retval false if help message was not displayed
 */
auto HandleHelp(int argc, char **argv) -> bool {
  if (argc < 3) {
    std::cout << "usage: dotmake [-h | --help] FILE TASK\n";
    return true;
  }
  for (int i{0}; i < argc; i++) {
    if (strncmp(argv[i], "--help", 6) == 0 || strncmp(argv[i], "-h", 2) == 0) {
      std::cout << "usage: dotmake [-h | --help] FILE TASK\n";
      return true;
    }
  }
  return false;
}

/**
 * @brief Entry point
 * @param argc Argument count
 * @param argv Argument values
 * @retval 0 on success
 * @retval 1 on failure
 */
auto main(int argc, char *argv[]) -> int {
  if (HandleHelp(argc, argv)) {
    return 0;
  }
  const std::string filename{argv[1]};
  const std::string name_task_to_run{argv[2]};

  if (!dotmake::yaml_parser::ParseFile<dotmake::Specification>(filename).Run(
          name_task_to_run)) {
    std::cerr << "Could not run task \"" << name_task_to_run << "\"\n";
    exit(EXIT_FAILURE);
  }

  return 0;
}
