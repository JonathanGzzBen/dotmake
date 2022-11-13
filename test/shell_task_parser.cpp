#include <gtest/gtest.h>
#include <shell_task_parser.h>

TEST(ShellTaskParser, ParseAndRunCorrect) {
  auto parsed_task = ShellTaskParser{"hello_task"}.parse_string(R"(

  type: shell
  commands:
    - echo "hello"

  )");

  ASSERT_TRUE(parsed_task.run());
}

TEST(ShellTaskParser, ParseWithoutCommands) {
  ASSERT_ANY_THROW(ShellTaskParser{"hello_task"}.parse_string(R"(

  type: shell
  commands:

  )"));
}

TEST(ShellTaskParser, ParseLinkTask) {
  ASSERT_ANY_THROW(ShellTaskParser{"hello_task"}.parse_string(R"(

  type: link
  links:
    some.txt: other.txt

  )"));
}
