#ifndef ABSTRACT_SYSTEM_CALLER_H
#define ABSTRACT_SYSTEM_CALLER_H

#include <cstdlib>
#include <string>
#ifdef _WIN32
#include <filesystem>
#endif

/**
 * @class AbstractSystemCaller
 *
 * @brief Makes system calls to run shell commands and make symbolic links
 */
class AbstractSystemCaller {
 public:
  virtual ~AbstractSystemCaller() = default;

  /**
   * @brief Runs shell command
   * @param cmd Command to run
   * @return System call result status
   */
  virtual inline int RunShellCommand(const std::string& cmd) const = 0;

  /**
   * @brief Creates a symbolic link
   * @param link Link path
   * @param target Target to which the link will point to
   * @param force Overwrite file or symlink if already exists
   * @return System call result status
   */
  virtual inline int CreateSymbolicLink(const std::string& link,
                                        const std::string& target,
                                        bool force = false) const = 0;
};

#endif  // ABSTRACT_SYSTEM_CALLER_H