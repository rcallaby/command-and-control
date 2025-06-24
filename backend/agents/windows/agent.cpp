#include <cpprest/http_client.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using json = nlohmann::json;

std::string SERVER_URL = "http://127.0.0.1:8080";
std::string AGENT_ID = "agent-windows-001";

void check_in() {
    http_client client(U(SERVER_URL + "/api/agent/checkin"));

    json j;
    j["agent_id"] = AGENT_ID;
    j["hostname"] = "windows-host";

    http_request req(methods::POST);
    req.headers().add(U("Content-Type"), U("application/json"));
    req.set_body(j.dump());

    client.request(req).then([](http_response response) {
        std::cout << "[+] Check-in response: " << response.status_code() << std::endl;
    }).wait();
}

int main() {
    while (true) {
        check_in();
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
