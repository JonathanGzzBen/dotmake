#include <dotmake/shell_task_parser.h>
#include <gtest/gtest.h>

#include "mock_system_caller.h"

using ::testing::Exactly;
using ::testing::Return;

TEST(ShellTaskParser, ParseAndRunCorrect) {
  auto parsed_task = dotmake::ShellTaskParser{"hello_task"}.ParseString(R"(

  type: shell
  commands:
    - echo "hello"

  )");

  MockSystemCaller mock_system_caller;

  EXPECT_CALL(mock_system_caller, RunShellCommand("echo \"hello\""))
      .Times(Exactly(1))
      .WillOnce(Return(0));

  auto test_task = dotmake::ShellTask{parsed_task, mock_system_caller};

  ASSERT_TRUE(test_task.Run());
}

TEST(ShellTaskParser, ParseWithoutCommands) {
  ASSERT_ANY_THROW(dotmake::ShellTaskParser{"hello_task"}.ParseString(R"(

  type: shell
  commands:

  )"));
}

TEST(ShellTaskParser, ParseLinkTask) {
  ASSERT_ANY_THROW(dotmake::ShellTaskParser{"hello_task"}.ParseString(R"(

  type: link
  links:
    some.txt: other.txt

  )"));
}
