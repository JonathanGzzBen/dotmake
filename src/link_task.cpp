#include "link_task.h"

dotmake::LinkTask::LinkTask(const LinkTask& link_task,
                            AbstractSystemCaller& abstract_system_caller)
    : Task{link_task.name, link_task.required_task_names},
      links{link_task.links},
      force{link_task.force},
      system_caller{abstract_system_caller} {}

dotmake::LinkTask::LinkTask(
    std::string name, std::vector<std::pair<std::string, std::string>> links,
    bool force, SystemCaller& system_caller)
    : Task{std::move(name)},
      links{std::move(links)},
      force{force},
      system_caller{system_caller} {}

auto dotmake::LinkTask::run() -> bool {
  for (const auto& link : links) {
    if (system_caller.CreateSymbolicLink(link.first, link.second) != 0) {
      std::cout << "Error creating link \"" << link.first << "\"\n";
      return false;
    }
  }
  return true;
}
