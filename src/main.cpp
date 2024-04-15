#include <getopt.h>

#include <cstring>
#include <iostream>
#include <string>

#include "dotmake/specification.h"
#include "dotmake/yaml_parser.h"

/**
 * @file main.cpp
 */

/**
 * @brief Entry point
 * @param argc Argument count
 * @param argv Argument values
 * @retval 0 on success
 * @retval 1 on failure
 */
auto main(int argc, char *argv[]) -> int {
  bool help{false};

  int opt;
  int option_index = 0;
  std::array<option, 4> long_options{
      {{"help", no_argument, nullptr, 'h'}, {nullptr, 0, nullptr, 0}}};
  while ((opt = getopt_long(argc, argv, "ho:v", long_options.data(),
                            &option_index)) != -1) {
    switch (opt) {
      case 'h':
        help = true;
        break;
      default:
        return 1;
    }
  }

  if (argc != (optind + 2)) {
    std::cout << "usage: dotmake [-h | --help] FILE TASK\n";
    return 0;
  }
  const std::string filename{argv[optind]};
  const std::string name_task_to_run{argv[optind + 1]};
  std::cout << "filename: " << filename << "\ntask: " << name_task_to_run
            << "\n";

  const auto specification =
      dotmake::yaml_parser::ParseFile<dotmake::Specification>(filename);

  if (help) {
    if (!specification.PrintHelpMessageForTask(name_task_to_run)) {
      std::cerr << "Could not print help message for task \""
                << name_task_to_run << "\"\n";
      exit(EXIT_FAILURE);
    }
  } else if (!specification.Run(name_task_to_run)) {
    std::cerr << "Could not run task \"" << name_task_to_run << "\"\n";
    exit(EXIT_FAILURE);
  }

  return 0;
}
