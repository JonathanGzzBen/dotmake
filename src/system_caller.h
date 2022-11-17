#ifndef SYSTEM_CALLER_H
#define SYSTEM_CALLER_H

#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <filesystem>
#endif

#include "abstract_system_caller.h"

/**
 * @class SystemCaller
 *
 * @brief Makes system calls to run shell commands and make symbolic links
 */
class SystemCaller final : public AbstractSystemCaller {
 private:
  SystemCaller() = default;

 public:
  SystemCaller(SystemCaller const&) = delete;
  virtual ~SystemCaller() = default;
  void operator=(SystemCaller const&) = delete;

  // SystemCaller is a singleton
  static SystemCaller& GetInstance();

  inline int RunShellCommand(const std::string& cmd) const override;

  inline int CreateSymbolicLink(const std::string& link,
                                const std::string& target,
                                bool force = false) const override;

  /**
   * @brief Get shell command to run command
   * @param cmd Command to run
   * @return Command to run (use powershell on Windows)
   */
  static inline std::string get_run_shell_command(const char* cmd);

  /**
   * @brief Get shell command to create symlink
   * @param link Symbolic link to create
   * @param target Target to which the symlink will point to
   * @return Command to run
   */
  static inline std::string get_link_command(const std::string& link,
                                             const std::string& target,
                                             bool force = false);
};

#endif  // SYSTEM_CALLER_H