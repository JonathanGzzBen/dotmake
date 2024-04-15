#include <gtest/gtest.h>

#include "dotmake/yaml_parser.h"
#include "mock_system_caller.h"

using ::testing::Exactly;
using ::testing::Return;
using namespace dotmake;

TEST(ShellTaskParser, ParseAndRunCorrect) {
  auto parsed_task = yaml_parser::ParseString<ShellTask>(R"(

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
  ASSERT_ANY_THROW(yaml_parser::ParseString<ShellTask>(R"(

  type: shell
  commands:

  )"));
}

TEST(ShellTaskParser, ParseWithHelpMesssage) {
  auto parsed_task = yaml_parser::ParseString<ShellTask>(R"(

  type: shell
  commands:
    - echo "hello"
  help: This task outputs "hello" to stdout

  )");

  const std::string expected = "This task outputs \"hello\" to stdout";

  EXPECT_EQ(parsed_task.GetHelpMessage(), expected);
}

TEST(ShellTaskParser, ParseLinkTask) {
  ASSERT_ANY_THROW(yaml_parser::ParseString<ShellTask>(R"(

  type: link
  links:
    some.txt: other.txt

  )"));
}
