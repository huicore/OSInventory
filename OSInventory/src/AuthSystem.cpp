#include "AuthSystem.h"
#include <algorithm>

AuthSystem::AuthSystem(Database& db) 
    : database(db), currentUser(nullptr) {}

bool AuthSystem::login(const std::string& username, const std::string& password) {
    User* user = database.findUserByUsername(username);
    if (user != nullptr && user->verifyPassword(password)) {
        currentUser = user;
        return true;
    }
    return false;
}

void AuthSystem::logout() {
    currentUser = nullptr;
}

bool AuthSystem::isLoggedIn() const {
    return currentUser != nullptr;
}

const User* AuthSystem::getCurrentUser() const {
    return currentUser;
}

bool AuthSystem::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    if (!isLoggedIn() || !currentUser->verifyPassword(oldPassword)) {
        return false;
    }
    
    // In a real application, we would update the hashed password in the database
    // For simplicity, we'll just update the user object
    User updatedUser = *currentUser;
    // Here we would call a method to update the password hash
    // updatedUser.setPasswordHash(hashPassword(newPassword));
    
    // Update in database
    if (database.updateUser(updatedUser)) {
        currentUser = database.findUserByUsername(currentUser->getUsername());
        return true;
    }
    
    return false;
}