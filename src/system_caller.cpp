#include "dotmake/system_caller.h"
// SystemCaller is a singleton
auto SystemCaller::GetInstance() -> SystemCaller& {
  static SystemCaller instance;
  return instance;
}

inline auto SystemCaller::RunShellCommand(const std::string& cmd) const -> int {
  return std::system((GetRunShellCommand(cmd.c_str()).c_str()));
}

inline auto SystemCaller::CreateSymbolicLink(const std::string& link,
                                             const std::string& target,
                                             bool force) const -> int {
  return std::system(GetLinkCommand(link, target, force).c_str());
}

inline auto SystemCaller::GetRunShellCommand(const char* cmd)
    -> std::string {
#ifdef _WIN32
  return std::string("powershell ") + cmd;
#else
  return cmd;
#endif
}

inline auto SystemCaller::GetLinkCommand(const std::string& link,
                                           const std::string& target,
                                           bool force) -> std::string {
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
