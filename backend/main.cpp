#include "crow_all.h"
#include "database.h"
#include "auth.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;
    Database db;

    // ====================== PUBLIC ROUTES ======================
    CROW_ROUTE(app, "/health")
    ([]() {
        return "OK";
    });

    // Login endpoint
    CROW_ROUTE(app, "/api/auth/login").methods("POST"_method)
    ([&db](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        std::string username = body["username"].s();
        std::string password = body["password"].s();  // TODO: hash + compare later

        // Placeholder auth - replace with real DB check
        if (username == "admin" && password == "admin123") {  // DEMO ONLY
            std::string token = g_auth.generate_token("user-1", username, {"admin", "operator"});
            json resp = {{"token", token}, {"user", username}};
            return crow::response(200, resp.dump());
        }

        return crow::response(401, "{\"error\": \"Invalid credentials\"}");
    });

    // ====================== PROTECTED ROUTES ======================
    CROW_ROUTE(app, "/api/agent/checkin").methods("POST"_method)
    ([&db](const crow::request& req) {
        return require_auth(req, [&](const std::string& user_id, const auto& roles) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400);

            std::string agent_id = body["agent_id"].s();
            std::string hostname = body["hostname"].s();

            db.add_or_update_agent(agent_id, hostname);

            json resp = {{"status", "ok"}, {"message", "Agent checked in"}};
            return crow::response(200, resp.dump());
        });
    });

    // Example: Protected agent listing
    CROW_ROUTE(app, "/api/agents").methods("GET"_method)
    ([&db](const crow::request& req) {
        return require_auth(req, [&](const std::string& user_id, const auto& roles) {
            // TODO: call AgentManager::list_agents()
            json agents = json::array();  // placeholder
            return crow::response(200, agents.dump());
        });
    });

    std::cout << "[*] C2 Server starting on port 8080 with JWT auth...\n";
    app.port(8080).multithreaded().run();
}