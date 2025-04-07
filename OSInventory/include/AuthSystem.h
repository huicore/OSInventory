#pragma once
#include "User.h"
#include "Database.h"

class AuthSystem {
public:
    AuthSystem(Database& db);
    
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isLoggedIn() const;
    const User* getCurrentUser() const;
    
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
    
private:
    Database& database;
    const User* currentUser;
};