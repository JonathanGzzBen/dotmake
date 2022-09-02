#ifndef TASK_H
#define TASK_H

#include <vector>
#include <memory>


class Task {
    protected:
        std::vector<std::shared_ptr<Task>> requirements;

        Task() {};
        Task(std::vector<std::shared_ptr<Task>> requirements): requirements{requirements} {};

        bool run_requirements() {
            for(const auto& task: requirements) {
                if(!task->run()) {
                    return false;
                }
            }
            return true;
        }

    public:
        virtual ~Task() = default;
        virtual bool run() = 0;
};
#endif //  TASK_H
