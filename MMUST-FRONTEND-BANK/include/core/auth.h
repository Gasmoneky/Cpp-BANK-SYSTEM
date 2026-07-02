#ifndef AUTH_H
#define AUTH_H
#include <string>

class Auth {
public:
    static bool login(const std::string& username, const std::string& password);
    enum AuthStatus {
        INITIALISING,
        NOT_AUTHENTICATED,
        AUTHENTICATED
    };