#include "auth.h"
#include <iostream>
#include <random>

AuthService g_auth;

AuthService::AuthService() {
    // In production: load from config file or environment variable
    secret_key_ = "your-super-secret-key-change-this-in-production-2026";
    // Better: std::getenv("JWT_SECRET") with fallback + warning
}

std::string AuthService::generate_token(const std::string& user_id,
                                        const std::string& username,
                                        const std::vector<std::string>& roles) {
    auto now = std::chrono::system_clock::now();

    auto token = jwt::create()
        .set_issuer(issuer_)
        .set_subject(user_id)
        .set_payload_claim("username", jwt::claim(username))
        .set_payload_claim("roles", jwt::claim(roles))
        .set_issued_at(now)
        .set_expires_at(now + std::chrono::hours(token_expiry_hours_))
        .sign(jwt::algorithm::hs256{secret_key_});

    return token;
}

std::optional<jwt::jwt_object> AuthService::validate_token(const std::string& token) {
    try {
        auto decoded = jwt::decode(token);
        jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{secret_key_})
            .with_issuer(issuer_)
            .verify(decoded);

        return decoded;
    } catch (const std::exception& e) {
        std::cerr << "[!] JWT validation failed: " << e.what() << std::endl;
        return std::nullopt;
    }
}

// Simple helper to be used in routes
crow::response require_auth(const crow::request& req,
                            std::function<crow::response(const std::string& user_id,
                                                       const std::vector<std::string>& roles)> handler) {
    std::string auth_header = req.get_header_value("Authorization");
    if (auth_header.empty() || auth_header.substr(0, 7) != "Bearer ") {
        return crow::response(401, "{\"error\": \"Missing or invalid Authorization header\"}");
    }

    std::string token = auth_header.substr(7);
    auto claims_opt = g_auth.validate_token(token);

    if (!claims_opt) {
        return crow::response(401, "{\"error\": \"Invalid or expired token\"}");
    }

    auto& claims = claims_opt.value();
    std::string user_id = claims.get_subject();
    std::vector<std::string> roles;

    if (claims.has_payload_claim("roles")) {
        auto roles_claim = claims.get_payload_claim("roles").as_array();
        for (const auto& r : roles_claim) {
            roles.push_back(r.as_string());
        }
    }

    return handler(user_id, roles);
}