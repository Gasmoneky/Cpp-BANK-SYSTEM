#pragma once
#include <string>

enum class AuthStatus {
    AUTHENTICATED,
    INITIALISING,
    NOT_AUTHENTICATED
};

class AuthManager {
private:

    AuthManager();

public:

    AuthManager(const AuthManager&) = delete;
    AuthManager& operator=(const AuthManager&) = delete;


    static AuthManager& getInstance();

    void saveSession(std::string jwtToken, std::string refreshToken);
    bool loadSession();

    void init(std::string jwtToken);

    std::string jwtToken;
    std::string refreshToken;
    AuthStatus currentStatus;
};
