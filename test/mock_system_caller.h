#ifndef MOCK_SYSTEM_CALLER_H
#define MOCK_SYSTEM_CALLER_H

#include <gmock/gmock.h>

#include "system_caller.h"

class MockSystemCaller : public SystemCaller {
 public:
  MockSystemCaller() = default;
  ~MockSystemCaller() override = default;
  void operator=(MockSystemCaller const&) {}

  static inline std::string get_link_command(const std::string& link,
                                             const std::string& target,
                                             bool force = false) {
    return SystemCaller::get_link_command(link, target, force);
  }

  static inline std::string get_run_shell_command(const char* cmd) {
    return SystemCaller::get_run_shell_command(cmd);
  }

  MOCK_METHOD(int, RunShellCommand, (const std::string& cmd),
              (const, override));
  MOCK_METHOD(int, CreateSymbolicLink,
              (const std::string& link, const std::string& target, bool force),
              (const, override));
};
#endif  // MOCK_SYSTEM_CALLER_H