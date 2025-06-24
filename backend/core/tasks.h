#pragma once

#include <string>
#include <vector>

struct Task {
    int id;
    std::string agent_id;
    std::string task_text;
    std::string status;
    std::string result;
};

class TaskManager {
public:
    void add_task(const Task& task);
    std::vector<Task> get_tasks_for_agent(const std::string& agent_id);
    void update_task_result(int task_id, const std::string& result);
};
