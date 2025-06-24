#pragma once
#include <pqxx/pqxx>
#include <iostream>

class Database {
public:
    Database() {
        conn = std::make_unique<pqxx::connection>("dbname=c2db user=c2user password=secret hostaddr=127.0.0.1 port=5432");
        if (conn->is_open()) {
            std::cout << "[*] Connected to database\n";
        }
    }

    void add_or_update_agent(const std::string& agent_id, const std::string& hostname) {
        pqxx::work W(*conn);
        W.exec_params(
            "INSERT INTO agents (agent_id, hostname) VALUES ($1, $2) "
            "ON CONFLICT (agent_id) DO UPDATE SET last_seen = CURRENT_TIMESTAMP",
            agent_id, hostname
        );
        W.commit();
    }

private:
    std::unique_ptr<pqxx::connection> conn;
};
