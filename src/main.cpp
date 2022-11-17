/**
 * @file main.cpp
 * @brief entry point for application
 * @mainpage dotmake

Tool inspired by GNU Make for applying dotfiles and configurations.

## Usage

Specifications can be specified using YAML files which should be given as
arguments to the `dotmake` command, followed by the name of the task to run:

```shell
usage: dotmake [-h | --help] FILE TASK
```

## Specification format

An specification file can hold multiple tasks, each has a `name` and a `type`,
let's take the following example:

```yaml
---
my_task_name: # This is the name of the task
  type: shell         # type of task
  commands: # shell task specific argument
    - echo "Hello"
```

It can also have a list of requirements, that is, a list of tasks that should be
run before that specific task is run. In this example, `shell_task_2` runs
before `shell_task_1` does:

```yaml
---
shell_task_1:
  type: shell
  requires:
    - shell_task_2
  commands:
    - dir

shell_task_2:
  type: shell
  commands:
    - pwd
```

Note: It does not matter the order in which tasks are declared in the
specification file.

## Types of tasks

### Shell

A shell task takes an array of string commands that are run secuentially in
default shell for POSIX systems and in PowerShell for Windows users.

```yaml
---
shell_task_1:
  type: shell
  commands:
    - dir
    - pwd
    - ls
```

### Link

A link task takes a sequence of objects to create links in the format `Link:
Target` where `Link` is the path to the symbolic link to be created and `Target`
the file to which it will point to. It can create symbolic links to files or
directories. Paths can be either relative or absolute.

```yaml
---
link_task_1:
  type: link
  links:
    hola: ..\filetolink.txt
    xd: ..\filetolink.txt
    idea: ..\.idea
```
 */

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "src/specification_parser.h"

/**
 * @brief Handles help message
 * @param argc Argument count
 * @param argv Argument values
 * @retval true if help message was displayed
 * @retval false if help message was not displayed
 */
auto HandleHelp(int argc, char *argv[]) -> bool {
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

  if (!dotmake::SpecificationParser{}.parse_file(filename).run(
          name_task_to_run)) {
    std::cerr << "Could not run task \"" << name_task_to_run << "\"\n";
    exit(EXIT_FAILURE);
  }
  return 0;
}
