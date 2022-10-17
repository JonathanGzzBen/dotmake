#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "src/specification_parser.h"

bool handle_help(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "usage: dotmake [-h | --help] FILE TASK\n";
    return true;
  }
  for (int i{0}; i < argc; i++) {
    if (strncmp(argv[i], "--help", 6) == 0) {
      std::cout << "usage: dotmake [-h | --help] FILE TASK\n";
      return true;
    }
    if (strncmp(argv[i], "-h", 2) == 0) {
      std::cout << "Print help\n";
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (handle_help(argc, argv)) {
    return 0;
  }
  const std::string filename{argv[1]};
  const std::string name_task_to_run{argv[2]};

  if (!SpecificationParser{}.parse_file(filename).run(name_task_to_run)) {
    std::cerr << "Could not run task \"" << name_task_to_run << "\"\n";
    exit(EXIT_FAILURE);
  }
  return 0;
}
