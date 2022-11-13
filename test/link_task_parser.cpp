#include <gtest/gtest.h>
#include <link_task_parser.h>
#include <shell_task_parser.h>
#include <stdlib.h>

#include <cstdlib>

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

TEST(LinkTaskParser, TryLinkingUnexistingFile) {
  auto test_task = LinkTaskParser{"test_task"}.parse_string(R"(

  type: link
  links:
    some.txt: other.txt

  )");

  ASSERT_FALSE(test_task.run());
}

TEST(LinkTaskParser, ParseWithoutCommands) {
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
