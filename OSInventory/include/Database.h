#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Asset.h"
#include "User.h"

class Database {
private:
    std::string dbPath;
    std::string assetsFile;
    std::string usersFile;
    std::vector<Asset> assets;
    std::vector<User> users;

public:
    explicit Database(const std::string& dbPath);
    Database(const std::string& assetsFile, const std::string& usersFile);

    // Asset operations
    bool addAsset(const Asset& asset);
    std::vector<Asset> getAllAssets() const;
    bool updateAsset(const Asset& asset);
    Asset* findAssetById(int id);
    std::vector<Asset> searchAssets(const std::string& query) const;

    // User operations
    bool addUser(const User& user);
    User* findUserByUsername(const std::string& username);
    std::vector<User> getAllUsers() const;
    bool updateUser(const User& user);

    // Statistics
    int getTotalAssets() const;
    double getTotalCost() const;

private:
    void loadAssets();
    void saveAssets() const;
    void loadUsers();
    void saveUsers() const;
};