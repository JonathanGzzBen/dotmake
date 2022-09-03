#include <string.h>

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "src/shell_task.h"
#include "src/shell_task_parser.h"
#include "src/specification.h"
#include "src/specification_parser.h"
#include "src/task.h"

bool handle_help(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "usage: dotmake [-h | --help] FILE... TASK\n";
    return true;
  }
  for (int i{0}; i < argc; i++) {
    if (strncmp(argv[i], "--help", 6) == 0) {
      std::cout << "usage: dotmake [-h | --help] FILE... TASK\n";
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

  auto spec = SpecificationParser{}.parse_file("test.yaml");

  for (const auto &task : spec.get_tasks()) {
    task.second->run();
  }

  return 0;
}
