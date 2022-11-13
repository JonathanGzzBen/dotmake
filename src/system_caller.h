#ifndef SYSTEM_CALLER_H
#define SYSTEM_CALLER_H

#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <filesystem>
#endif

static inline std::string get_run_shell_command(const char* cmd) {
#ifdef _WIN32
  return std::string("powershell ") + cmd;
#else
  return cmd;
#endif
}

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

class SystemCaller {
 protected:
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

  virtual inline int RunShellCommand(const std::string& cmd) const {
    return std::system((get_run_shell_command(cmd.c_str()).c_str()));
  }

  virtual inline int CreateSymbolicLink(const std::string& link,
                                        const std::string& target,
                                        bool force = false) const {
    return std::system(get_link_command(link, target, force).c_str());
  }
};

#endif  // SYSTEM_CALLER_H