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
  static SystemCaller& GetInstance() {
    static SystemCaller instance;
    return instance;
  }

  inline int RunShellCommand(const std::string& cmd) const override {
    return std::system((get_run_shell_command(cmd.c_str()).c_str()));
  }

  inline int CreateSymbolicLink(const std::string& link,
                                const std::string& target,
                                bool force = false) const override {
    return std::system(get_link_command(link, target, force).c_str());
  }

  /**
   * @brief Get shell command to run command
   * @param cmd Command to run
   * @return Command to run (use powershell on Windows)
   */
  static inline std::string get_run_shell_command(const char* cmd) {
#ifdef _WIN32
    return std::string("powershell ") + cmd;
#else
    return cmd;
#endif
  }

  /**
   * @brief Get shell command to create symlink
   * @param link Symbolic link to create
   * @param target Target to which the symlink will point to
   * @return Command to run
   */
  static inline std::string get_link_command(const std::string& link,
                                             const std::string& target,
                                             bool force = false) {
#ifdef _WIN32
    std::filesystem::path target_path{target};
    std::string command =
        "cmd /c mklink " +
        std::string(std::filesystem::is_directory(target_path) ? "/D " : "") +
        link + " " + target;
#else
    std::string command{std::string{"ln "} +
                        std::string{force ? "-svnf" : "-snv"} +
                        std::string{" \"$PWD/"} + target + "\" " + link};
#endif
    return command;
  }
};

#endif  // SYSTEM_CALLER_H