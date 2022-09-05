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

  auto spec = SpecificationParser{}.parse_file("test.yaml");

  const auto &task_to_run = spec.get_tasks()[name_task_to_run];
  if (task_to_run == nullptr) {
    std::cout << "There is no task with name \"" << name_task_to_run
              << "\"  in specification file\n";
    return 1;
  }

  task_to_run->run();
  return 0;
}
