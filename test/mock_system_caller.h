#ifndef MOCK_SYSTEM_CALLER_H
#define MOCK_SYSTEM_CALLER_H

#include <gmock/gmock.h>

#include "system_caller.h"

class MockSystemCaller : public SystemCaller {
 public:
  MockSystemCaller() = default;
  ~MockSystemCaller() override = default;
  void operator=(MockSystemCaller const&) {}

  MOCK_METHOD(int, RunShellCommand, (const std::string& cmd), (const, override));
  MOCK_METHOD(int, CreateSymbolicLink,
              (const std::string& link, const std::string& target, bool force),
              (const, override));
};
#endif  // MOCK_SYSTEM_CALLER_H