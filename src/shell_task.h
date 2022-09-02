#ifndef SHELL_TASK_H
#define SHELL_TASK_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "src/task.h"


class ShellTask: public Task {
    private:
        std::vector<std::string> commands;
    public:
        ShellTask(std::vector<std::string> commands): Task{}, commands{commands} {}
        ShellTask(std::vector<std::shared_ptr<Task>> requirements): Task{requirements} {}
        virtual ~ShellTask() = default;


        bool run() override {
            this->run_requirements();
            for(const auto& command: commands) {
                if (std::system(command.c_str())) {
                    std::cout << "Error in command: " << command << "\n";
                    return false;
                }
            }
            return true;
        }
};
#endif //  SHELL_TASK_H
