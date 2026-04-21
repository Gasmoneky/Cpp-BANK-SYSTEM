#ifndef AUTH_H
#define AUTH_H

#include <string>

namespace Core {

    enum class AuthStatus { 
        INITIALIZING, 
        LOGGED_OUT, 
        LOGGED_IN, 
        AUTH_FAILED 
    };

    class AuthManager {
    public:
        static AuthManager& getInstance();

        // The new initialization call
        void init(); 

        bool login(const std::string& username, const std::string& password);
        void logout();
        
        AuthStatus getStatus() const { return currentStatus; }
        std::string getLastError() const { return lastError; }

    private:
        AuthManager(); 
        
        AuthStatus currentStatus;
        std::string jwtToken;
        std::string lastError;

        // Persistence helpers
        void saveSession();
        bool loadSession();
    };
}

#endif