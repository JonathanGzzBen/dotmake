# dotmake

Tool inspired by GNU Make for applying dotfiles and configurations.

## Usage

Specifications can be specified using YAML files which should be given as arguments to the `dotmake` command, followed
by the name of the task to run:

```shell
usage: dotmake [-h | --help] FILE TASK
```

## Specification format

An specification file can hold multiple tasks, each has a `name` and a `type`, let's take the following example:

```yaml
---
my_task_name: # This is the name of the task
  type: shell         # type of task
  commands: # shell task specific argument
    - echo "Hello"
```

It can also have a list of requirements, that is, a list of tasks that should be run before that specific task is run.
In this example, `shell_task_2` runs before `shell_task_1` does:

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

Note: It does not matter the order in which tasks are declared in the specification file.

## Types of tasks

### Shell

A shell task takes an array of string commands that are run secuentially in default shell for POSIX systems and in
PowerShell for Windows users.

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

A link task takes a sequence of objects to create links in the format `Link: Target` where `Link` is the path to the
symbolic link to be created and `Target` the file to which it will point to. It can create symbolic links to files or
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

## TODO

- Add option to print help for each task
- Add a way to specify command-line arguments for tasks
- Add all classes to Doxygen docs
- Move `*.cpp` files from `include/dotmake` to `src`
