#include CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"
#include "authservice.h"
#include <iostream>

using json = nlohmann::json;

json AuthService::login(const std::string& username, const std::string& password) {
    httplib::SSLClient cli("https://localhost:8080",443);
    json loginPayload = {
        {"username", username},
        {"password", password}
    };
    auto res = cli.Post("/api/login", loginPayload.dump(), "application/json");
    if (res && res->status == 200) {
        try
        return json::parse(res->body);
    } else {
        throw std::runtime_error("Login failed: " + (res ? res->body : "No response"));
    }
}