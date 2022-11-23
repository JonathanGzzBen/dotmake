#ifndef MOCK_SYSTEM_CALLER_H
#define MOCK_SYSTEM_CALLER_H

#include <gmock/gmock.h>

#include "dotmake/abstract_system_caller.h"

class MockSystemCaller : public AbstractSystemCaller {
 public:
  MockSystemCaller() = default;
  ~MockSystemCaller() override = default;

  MOCK_METHOD(int, RunShellCommand, (const std::string& cmd),
              (const, override));
  MOCK_METHOD(int, CreateSymbolicLink,
              (const std::string& link, const std::string& target, bool force),
              (const, override));
};
#endif  // MOCK_SYSTEM_CALLER_H
