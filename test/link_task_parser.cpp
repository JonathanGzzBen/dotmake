#include <gtest/gtest.h>
#include <link_task_parser.h>
#include <shell_task_parser.h>
#include <stdlib.h>

#include <cstdlib>

#include "mock_system_caller.h"

using ::testing::Exactly;
using ::testing::Return;

TEST(GetLinkCommand, LinkFile) {
  EXPECT_EQ(get_link_command("link.txt", "target.txt"),
            "cmd /c mklink link.txt target.txt");
}

TEST(GetLinkCommand, LinkDirectory) {
  std::filesystem::create_directory("dirtolink");
#ifdef _WIN32
  const std::string expected = "cmd /c mklink /D linkeddir dirtolink";
#else
  const std::string expected = "ln -snv \"$PWD/dirtolink\" linkeddir";
#endif
  EXPECT_EQ(get_link_command("linkeddir", "dirtolink"), expected);
  std::filesystem::remove("dirtolink");
}

TEST(LinkTaskParser, LinkFileNoForce) {
  auto parsed_task = LinkTaskParser{"test_task"}.parse_string(R"(

  type: link
  links:
    link.txt: target.txt

  )");

  MockSystemCaller mock_system_caller;

  EXPECT_CALL(mock_system_caller,
              CreateSymbolicLink("link.txt", "target.txt", false))
      .Times(Exactly(1))
      .WillOnce(Return(0));

  auto test_task = LinkTask{parsed_task, mock_system_caller};

  ASSERT_TRUE(test_task.run());
}

TEST(LinkTaskParser, ParseWithoutLinks) {
  ASSERT_ANY_THROW(LinkTaskParser{"test_task"}.parse_string(R"(

  type: link
  links:

  )"));
}

TEST(LinkTaskParser, ParseShellTask) {
  ASSERT_ANY_THROW(LinkTaskParser{"test_task"}.parse_string(R"(

  type: shell
  commands:
    - echo "hello"

  )"));
}
