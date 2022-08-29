#include <string.h>

#include <iostream>
#include <thread>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "usage: dotmake [-h | --help] FILE... TASK\n";
    return 0;
  }
  for (int i{0}; i < argc; i++) {
    if (strncmp(argv[i], "--help", 6) == 0) {
      std::cout << "usage: dotmake [-h | --help] FILE... TASK\n";
      return 0;
    }
    if (strncmp(argv[i], "-h", 2) == 0) {
      std::cout << "Print help\n";
      return 0;
    }
  }
  return 0;
}
