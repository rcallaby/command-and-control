#pragma once
#include "crow_all.h"
#include <jwt-cpp/jwt.h>
#include <string>
#include <chrono>
#include <optional>

class AuthService {
public:
    AuthService();

    // Generate JWT for operator
    std::string generate_token(const std::string& user_id,
                               const std::string& username,
                               const std::vector<std::string>& roles);

    // Verify token and return claims
    std::optional<jwt::jwt_object> validate_token(const std::string& token);

    // Middleware for Crow
    crow::middleware::returnable auth_middleware(const crow::request& req,
                                                 std::string& user_id,
                                                 std::vector<std::string>& roles);

private:
    std::string secret_key_;
    std::string issuer_ = "c2server";
    int token_expiry_hours_ = 24;
};

extern AuthService g_auth;  // Global singleton for simplicity (or inject it)