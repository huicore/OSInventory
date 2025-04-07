#include "User.h"
#include <functional> // Äëÿ std::hash
#include <sstream>

// Simple hash function for demonstration purposes
// In a real application, use a proper cryptographic hash like bcrypt
std::string User::hashPassword(const std::string& password) const {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

User::User(const std::string& username, const std::string& password, 
           const std::string& fullName, UserRole role)
    : username(username), 
      passwordHash(hashPassword(password)),
      fullName(fullName), 
      role(role) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getFullName() const {
    return fullName;
}

UserRole User::getRole() const {
    return role;
}

bool User::verifyPassword(const std::string& password) const {
    return passwordHash == hashPassword(password);
}

bool User::isAdmin() const {
    return role == UserRole::ADMIN;
}

bool User::isEditor() const {
    return role == UserRole::EDITOR;
}

bool User::isViewer() const {
    return role == UserRole::VIEWER;
}

std::string User::serialize() const {
    std::ostringstream oss;
    oss << username << "|" << passwordHash << "|" << fullName << "|" << static_cast<int>(role);
    return oss.str();
}

User User::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() != 4) {
        throw std::runtime_error("Invalid user data format");
    }
    
    return User(
        tokens[0], 
        "", // Password is not stored in plain text, we only have the hash
        tokens[2], 
        static_cast<UserRole>(std::stoi(tokens[3]))
    );
}