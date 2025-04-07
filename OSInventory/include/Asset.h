#pragma once
#include <string>
#include <ctime>
#include <vector>

class Asset {
public:
    Asset(int id, const std::string& name, const std::string& invNumber, 
          const std::string& model, const std::string& serialNumber,
          const std::string& location, const std::string& responsible,
          const std::string& status, double cost, const std::string& receiptDate,
          const std::string& commissioningDate, const std::string& writeOffDate,
          const std::string& notes);
	Asset() : id(0), cost(0.0) {}

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getInvNumber() const;
    std::string getModel() const;
    std::string getSerialNumber() const;
    std::string getLocation() const;
    std::string getResponsible() const;
    std::string getStatus() const;
    double getCost() const;
    std::string getReceiptDate() const;
    std::string getCommissioningDate() const;
    std::string getWriteOffDate() const;
    std::string getNotes() const;

    // Setters
    void setName(const std::string& name);
    void setInvNumber(const std::string& invNumber);
    void setModel(const std::string& model);
    void setSerialNumber(const std::string& serialNumber);
    void setLocation(const std::string& location);
    void setResponsible(const std::string& responsible);
    void setStatus(const std::string& status);
    void setCost(double cost);
    void setReceiptDate(const std::string& receiptDate);
    void setCommissioningDate(const std::string& commissioningDate);
    void setWriteOffDate(const std::string& writeOffDate);
    void setNotes(const std::string& notes);

    // Serialization
    std::string serialize() const;
    static Asset deserialize(const std::string& data);

private:
    int id;
    std::string name;
    std::string invNumber;
    std::string model;
    std::string serialNumber;
    std::string location;
    std::string responsible;
    std::string status;
    double cost;
    std::string receiptDate;
    std::string commissioningDate;
    std::string writeOffDate;
    std::string notes;
};