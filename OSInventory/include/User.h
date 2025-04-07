#pragma once
#include <string>

enum class UserRole {
    ADMIN,
    EDITOR,
    VIEWER
};

class User {
public:
    User(const std::string& username, const std::string& password, 
         const std::string& fullName, UserRole role);
    
    // Getters
    std::string getUsername() const;
    std::string getFullName() const;
    UserRole getRole() const;
    
    // Password verification
    bool verifyPassword(const std::string& password) const;
    
    // Role checks
    bool isAdmin() const;
    bool isEditor() const;
    bool isViewer() const;
    
    // Serialization
    std::string serialize() const;
    static User deserialize(const std::string& data);
    
private:
    std::string username;
    std::string passwordHash; // In real app, store hashed password
    std::string fullName;
    UserRole role;
    
    std::string hashPassword(const std::string& password) const;
};