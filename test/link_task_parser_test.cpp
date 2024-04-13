#include <gtest/gtest.h>

#include <filesystem>

#include "dotmake/yaml_parser.h"
#include "mock_system_caller.h"

using ::testing::Exactly;
using ::testing::Return;

TEST(GetLinkCommand, LinkFile) {
#ifdef _WIN32
  std::string expected = "cmd /c mklink link.txt target.txt";
#else
  std::string expected = "ln -snv \"$PWD/target.txt\" link.txt";
#endif
  EXPECT_EQ(SystemCaller::GetLinkCommand("link.txt", "target.txt"), expected);
}

TEST(GetLinkCommand, LinkDirectory) {
  std::filesystem::create_directory("dirtolink");
#ifdef _WIN32
  const std::string expected = "cmd /c mklink /D linkeddir dirtolink";
#else
  const std::string expected = "ln -snv \"$PWD/dirtolink\" linkeddir";
#endif
  EXPECT_EQ(SystemCaller::GetLinkCommand("linkeddir", "dirtolink"), expected);
  std::filesystem::remove("dirtolink");
}

TEST(LinkTaskParser, LinkFileNoForce) {
  auto parsed_task = dotmake::yaml_parser::ParseString<dotmake::LinkTask>(R"(

  type: link
  links:
    link.txt: target.txt

  )");

  MockSystemCaller mock_system_caller;

  EXPECT_CALL(mock_system_caller,
              CreateSymbolicLink("link.txt", "target.txt", false))
      .Times(Exactly(1))
      .WillOnce(Return(0));

  auto test_task = dotmake::LinkTask{parsed_task, mock_system_caller};

  ASSERT_TRUE(test_task.Run());
}

TEST(LinkTaskParser, ParseWithoutLinks) {
  ASSERT_ANY_THROW(dotmake::yaml_parser::ParseString<dotmake::LinkTask>(R"(

  type: link
  links:

  )"));
}

TEST(LinkTaskParser, ParseShellTask) {
  ASSERT_ANY_THROW(dotmake::yaml_parser::ParseString<dotmake::LinkTask>(R"(

  type: shell
  commands:
    - echo "hello"

  )"));
}
