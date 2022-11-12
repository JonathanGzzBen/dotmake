#ifndef LINK_TASK_H
#define LINK_TASK_H

/**
 * @file link_task.h
 * @brief LinkTask class
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "src/task.h"

#ifdef _WIN32
#include <filesystem>
#endif

/**
 * @class LinkTask
 *
 * @brief A task that creates symbolic links
 */
class LinkTask : public Task {
 private:
  std::vector<std::pair<std::string, std::string>> links;
  bool force;

 public:
  LinkTask(std::string name,
           std::vector<std::pair<std::string, std::string>> links, bool force)
      : Task{name}, links{links}, force{force} {}
  virtual ~LinkTask() = default;

  virtual bool run() override {
    for (const auto& link : links) {
#ifdef _WIN32
      std::filesystem::path file_path(link.second.c_str());
      std::string command =
          "cmd /c mklink " +
          std::string(std::filesystem::is_directory(file_path) ? "/D " : " ") +
          link.first + " " + link.second;
#else
      std::string command{
          std::string{"ln "} + std::string{force ? "-svnf" : "-snv"} +
          std::string{" \"$PWD/"} + link.second + "\" " + link.first};
#endif
      if (std::system(command.c_str())) {
        std::cout << "Error in command: " << command << "\n";
        return false;
      }
    }
    return true;
  }
};
#endif  //  LINK_TASK_H
