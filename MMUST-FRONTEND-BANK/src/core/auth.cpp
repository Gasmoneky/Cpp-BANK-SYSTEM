#include "core/auth.h"
#include <fstream>
#include <filesystem>

namespace Core {

    AuthManager& AuthManager::getInstance() {
        static AuthManager instance;
        return instance;
    }

    AuthManager::AuthManager() : currentStatus(AuthStatus::INITIALIZING) {}

    void AuthManager::init() {
        // Try to load a session from a file on your Linux system
        if (loadSession()) {
            // In a pro version, you'd ping the Droplet here to verify the JWT
            this->currentStatus = AuthStatus::LOGGED_IN;
        } else {
            this->currentStatus = AuthStatus::LOGGED_OUT;
        }
    }

    bool AuthManager::login(const std::string& username, const std::string& password) {
        // ... (Your httplib code to talk to DigitalOcean) ...
        
        // On success:
        this->jwtToken = "received_token_from_server";
        saveSession(); // Persist it so init() finds it next time
        this->currentStatus = AuthStatus::LOGGED_IN;
        return true;
    }

    void AuthManager::saveSession() {
        std::ofstream file("session.jwt");
        if (file.is_open()) {
            file << jwtToken;
            file.close();
        }
    }

    bool AuthManager::loadSession() {
        if (std::filesystem::exists("session.jwt")) {
            std::ifstream file("session.jwt");
            std::getline(file, jwtToken);
            return !jwtToken.empty();
        }
        return false;
    }

    void AuthManager::logout() {
        this->jwtToken = "";
        std::filesystem::remove("session.jwt"); // Clean up the file
        this->currentStatus = AuthStatus::LOGGED_OUT;
    }
}