#include "core/auth.h"
#include "ui/signin_authui.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
using json = nlohmann::json;

    AuthManager& AuthManager::getInstance() {
        static AuthManager instance;
        return instance;
    }

AuthManager::AuthManager(){
    currentStatus = AuthStatus::NOT_AUTHENTICATED;
}

void AuthManager::saveSession(std::string jwtToken,std::string refreshToken){
   auto now = std::chrono::system_clock::now();
   auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    json sessionData ;
    sessionData["access_token"] = this->jwtToken;
    sessionData["last_activity"] = now_seconds;
std::ofstream file("session.jwt");
if (file.is_open()) {
    file << sessionData.dump(4);
    file.close();
    std::cout << "[AUTH]Session saved successfully. Timestamp: " << now_seconds << std::endl;
} else {
    std::cerr << "[AUTH]Failed to save session." << std::endl;
    }
}
bool AuthManager::loadSession(){
    if(!std::filesystem::exists("session.jwt")) {
        std::cout << "[AUTH]No session file found." << std::endl;
        return false;
    }
    json data;
    try{
        std::ifstream file("session.jwt");
        data = json::parse(file);
        }
        catch(...){
            std::cerr << "[AUTH]Failed to load session: " << std::endl;
            return false;
        }
        if(!data.contains("access_token")||!data.contains("last_activity")){
            std::cerr << "[AUTH]Invalid session file format." << std::endl;
            return false;
        }
  long long lastActivity = data["last_activity"];
  auto now = std::chrono::system_clock::now();
  auto currentTimeSeconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
  if(currentTimeSeconds - lastActivity > 7200){
        std::cout << "[AUTH]Session expired." << std::endl;
        return false;
    }
this->jwtToken = data["access_token"];
std::cout << "[AUTH]Session loaded successfully. Last activity: " << lastActivity << std::endl;
return true;

}

void AuthManager::init(std::string jwtToken){
    std::cout << "[AUTH]Initializing authentication manager..." << std::endl;
    if(loadSession()){
        currentStatus = AuthStatus::AUTHENTICATED;
        std::cout << "[AUTH]User authenticated via existing session." << std::endl;
        std::cout<<"Valid json token"<<jwtToken<<std::endl;
    } else {
        currentStatus = AuthStatus::NOT_AUTHENTICATED;
        std::cout << "[AUTH]No valid session found. User not authenticated." << std::endl;
        jwtToken = "";
        refreshToken = "";
        std::cout<<"No valid session found....Redirecting to login screen..."<<jwtToken<<std::endl;
    }
}
