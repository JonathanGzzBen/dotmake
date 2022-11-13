#include <gtest/gtest.h>
#include <shell_task_parser.h>

#include "mock_system_caller.h"

using ::testing::Exactly;
using ::testing::Return;

TEST(ShellTaskParser, ParseAndRunCorrect) {
  auto parsed_task = ShellTaskParser{"hello_task"}.parse_string(R"(

  type: shell
  commands:
    - echo "hello"

  )");

  MockSystemCaller mock_system_caller;

  EXPECT_CALL(mock_system_caller, RunShellCommand("echo \"hello\""))
      .Times(Exactly(1))
      .WillOnce(Return(0));

  auto test_task = ShellTask{parsed_task, mock_system_caller};

  ASSERT_TRUE(test_task.run());
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
