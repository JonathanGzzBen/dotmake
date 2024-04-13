#include "dotmake/link_task.h"

#include <iostream>

dotmake::LinkTask::LinkTask(const LinkTask& link_task,
                            AbstractSystemCaller& abstract_system_caller)
    : Task{link_task.name_, link_task.required_task_names_},
      links_{link_task.links_},
      force_{link_task.force_},
      system_caller_{abstract_system_caller} {}

dotmake::LinkTask::LinkTask(
    std::string name, std::vector<std::pair<std::string, std::string>> links,
    bool force, SystemCaller& system_caller)
    : Task{std::move(name)},
      links_{std::move(links)},
      force_{force},
      system_caller_{system_caller} {}

auto dotmake::LinkTask::Run() -> bool {
  for (const auto& link : links_) {
    if (system_caller_.CreateSymbolicLink(link.first, link.second) != 0) {
      std::cout << "Error creating link \"" << link.first << "\"\n";
      return false;
    }
  }
  return true;
}
