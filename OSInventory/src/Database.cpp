#include "Database.h"
#include "Asset.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Database::Database(const std::string& dbPath) :
    dbPath(dbPath),
    assetsFile(dbPath + "_assets.dat"),
    usersFile(dbPath + "_users.dat")
{
    std::cout << "Initializing database with path: " << dbPath << std::endl;

    // Загрузка данных
    loadAssets();
    loadUsers();

    // Создание администратора, если пользователей нет
    if (users.empty()) {
        User admin("admin", "admin123", "Administrator", UserRole::ADMIN);
        addUser(admin);
    }
}

Database::Database(const std::string& assetsFile, const std::string& usersFile) :
    assetsFile(assetsFile),
    usersFile(usersFile)
{
    loadAssets();
    loadUsers();

    if (users.empty()) {
        User admin("admin", "admin123", "Administrator", UserRole::ADMIN);
        addUser(admin);
    }
}

bool Database::addAsset(const Asset& asset) {
    if (findAssetById(asset.getId()) != nullptr) {
        return false;
    }
    assets.push_back(asset);
    saveAssets();
    return true;
}

std::vector<Asset> Database::getAllAssets() const {
    return assets;
}

bool Database::updateAsset(const Asset& asset) {
    auto it = std::find_if(assets.begin(), assets.end(),
        [&asset](const Asset& a) { return a.getId() == asset.getId(); });

    if (it != assets.end()) {
        *it = asset;
        saveAssets();
        return true;
    }
    return false;
}

Asset* Database::findAssetById(int id) {
    auto it = std::find_if(assets.begin(), assets.end(),
        [id](const Asset& a) { return a.getId() == id; });
    return it != assets.end() ? &(*it) : nullptr;
}

std::vector<Asset> Database::searchAssets(const std::string& query) const {
    std::vector<Asset> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& asset : assets) {
        std::string name = asset.getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name.find(lowerQuery) != std::string::npos) {
            results.push_back(asset);
        }
    }
    return results;
}

bool Database::addUser(const User& user) {
    if (findUserByUsername(user.getUsername()) != nullptr) {
        return false;
    }
    users.push_back(user);
    saveUsers();
    return true;
}

bool Database::updateUser(const User& user) {
    auto it = std::find_if(users.begin(), users.end(),
        [&user](const User& u) { return u.getUsername() == user.getUsername(); });

    if (it != users.end()) {
        *it = user;
        saveUsers();
        return true;
    }
    return false;
}

void Database::loadUsers() {
    users.clear();
    std::ifstream file(usersFile);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        try {
            users.push_back(User::deserialize(line));
        }
        catch (...) {
            // Пропускаем некорректные строки
        }
    }
}

void Database::saveUsers() const {
    std::ofstream file(usersFile);
    if (!file.is_open()) return;

    for (const auto& user : users) {
        file << user.serialize() << "\n";
    }
}

User* Database::findUserByUsername(const std::string& username) {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const User& u) { return u.getUsername() == username; });
    return it != users.end() ? &(*it) : nullptr;
}

void Database::loadAssets() {
    assets.clear();
    std::ifstream file(assetsFile);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        try {
            assets.push_back(Asset::deserialize(line));
        }
        catch (...) {
            // Пропускаем некорректные строки
        }
    }
}

void Database::saveAssets() const {
    std::ofstream file(assetsFile);
    if (!file.is_open()) return;

    for (const auto& asset : assets) {
        file << asset.serialize() << "\n";
    }
}