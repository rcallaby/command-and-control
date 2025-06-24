#pragma once

#include <string>
#include <vector>

struct Agent {
    std::string agent_id;
    std::string hostname;
    std::string last_seen;
};

class AgentManager {
public:
    void register_agent(const Agent& agent);
    std::vector<Agent> list_agents();
};
