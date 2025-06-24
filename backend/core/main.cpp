#include "crow_all.h"
#include "database.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;
    Database db;

    CROW_ROUTE(app, "/health")
    ([](){
        return "OK";
    });

    CROW_ROUTE(app, "/api/agent/checkin").methods("POST"_method)
    ([&db](const crow::request& req){
        auto body = crow::json::load(req.body);
        std::string agent_id = body["agent_id"].s();
        std::string hostname = body["hostname"].s();

        db.add_or_update_agent(agent_id, hostname);

        return crow::response(200, "{\"status\": \"ok\"}");
    });

    app.port(8080).multithreaded().run();
}
