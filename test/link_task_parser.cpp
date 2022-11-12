#include <gtest/gtest.h>
#include <shell_task_parser.h>
#include <link_task_parser.h>

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
