#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cpprest/http_client.h>
#include <nlohmann/json.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using json = nlohmann::json;

const std::string SERVER_URL = "http://127.0.0.1:8080";

void list_agents() {
    try {
        http_client client(U(SERVER_URL + "/api/agents"));
        http_request req(methods::GET);

        auto response = client.request(req).get();
        if (response.status_code() == 200) {
            auto body = response.extract_string().get();
            auto j = json::parse(body);

            std::cout << "\n[*] Registered Agents:\n";
            for (const auto& agent : j["agents"]) {
                std::cout << " - ID: " << agent["agent_id"] << " | Hostname: " << agent["hostname"] 
                          << " | Last Seen: " << agent["last_seen"] << "\n";
            }
        } else {
            std::cerr << "[-] Failed to list agents. Status: " << response.status_code() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[-] Exception: " << e.what() << "\n";
    }
}

void send_task(const std::string& agent_id, const std::string& task_text) {
    try {
        http_client client(U(SERVER_URL + "/api/tasks"));
        json j;
        j["agent_id"] = agent_id;
        j["task_text"] = task_text;

        http_request req(methods::POST);
        req.headers().add(U("Content-Type"), U("application/json"));
        req.set_body(j.dump());

        auto response = client.request(req).get();
        if (response.status_code() == 200) {
            std::cout << "[+] Task sent to agent " << agent_id << "\n";
        } else {
            std::cerr << "[-] Failed to send task. Status: " << response.status_code() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[-] Exception: " << e.what() << "\n";
    }
}

void view_results(const std::string& agent_id) {
    try {
        http_client client(U(SERVER_URL + "/api/results?agent_id=" + agent_id));
        http_request req(methods::GET);

        auto response = client.request(req).get();
        if (response.status_code() == 200) {
            auto body = response.extract_string().get();
            auto j = json::parse(body);

            std::cout << "\n[*] Task Results for Agent: " << agent_id << "\n";
            for (const auto& result : j["results"]) {
                std::cout << "Task ID: " << result["task_id"] 
                          << " | Status: " << result["status"] 
                          << " | Result: " << result["result"] << "\n";
            }
        } else {
            std::cerr << "[-] Failed to get results. Status: " << response.status_code() << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "[-] Exception: " << e.what() << "\n";
    }
}

void print_help() {
    std::cout << R"(

[*] C2 CLI Commands:

    list-agents               - List all registered agents
    send-task <agent_id> <task_text>  - Send a task to an agent
    view-results <agent_id>   - View task results for an agent
    help                      - Show this help message
    exit                      - Exit CLI

)";
}

int main() {
    std::cout << "[*] C2 CLI client ready.\n";
    print_help();

    std::string line;
    while (true) {
        std::cout << "c2cli> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "list-agents") {
            list_agents();
        }
        else if (cmd == "send-task") {
            std::string agent_id, task_text;
            iss >> agent_id;
            std::getline(iss, task_text);
            if (agent_id.empty() || task_text.empty()) {
                std::cout << "Usage: send-task <agent_id> <task_text>\n";
            } else {
                send_task(agent_id, task_text.substr(1)); // remove leading space
            }
        }
        else if (cmd == "view-results") {
            std::string agent_id;
            iss >> agent_id;
            if (agent_id.empty()) {
                std::cout << "Usage: view-results <agent_id>\n";
            } else {
                view_results(agent_id);
            }
        }
        else if (cmd == "help") {
            print_help();
        }
        else if (cmd == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command: " << cmd << "\n";
            print_help();
        }
    }

    std::cout << "[*] Exiting C2 CLI client.\n";
    return 0;
}
