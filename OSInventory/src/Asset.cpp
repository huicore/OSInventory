#include "Asset.h"
#include <sstream>
#include <iomanip>

Asset::Asset(int id, const std::string& name, const std::string& invNumber, 
             const std::string& model, const std::string& serialNumber,
             const std::string& location, const std::string& responsible,
             const std::string& status, double cost, const std::string& receiptDate,
             const std::string& commissioningDate, const std::string& writeOffDate,
             const std::string& notes)
    : id(id), name(name), invNumber(invNumber), model(model), 
      serialNumber(serialNumber), location(location), responsible(responsible),
      status(status), cost(cost), receiptDate(receiptDate), 
      commissioningDate(commissioningDate), writeOffDate(writeOffDate), notes(notes) {}

// Getters implementation
int Asset::getId() const { return id; }
std::string Asset::getName() const { return name; }
std::string Asset::getInvNumber() const { return invNumber; }
// ... other getters

// Setters implementation
void Asset::setName(const std::string& name) { this->name = name; }
void Asset::setInvNumber(const std::string& invNumber) { this->invNumber = invNumber; }
// ... other setters

std::string Asset::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << invNumber << "|" << model << "|"
        << serialNumber << "|" << location << "|" << responsible << "|"
        << status << "|" << cost << "|" << receiptDate << "|"
        << commissioningDate << "|" << writeOffDate << "|" << notes;
    return oss.str();
}

Asset Asset::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() != 13) {
        throw std::runtime_error("Invalid asset data format");
    }
    
    return Asset(
        std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4],
        tokens[5], tokens[6], tokens[7], std::stod(tokens[8]), tokens[9],
        tokens[10], tokens[11], tokens[12]
    );
}