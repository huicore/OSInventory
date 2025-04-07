#include "GUI.h"
#include "Database.h"
#include "AuthSystem.h"
#include <memory>
#include <iostream> // Äëÿ std::cerr

int main() {
    setlocale(LC_ALL, "Russian");
    Database db("database_storage");
    AuthSystem auth(db);
    try {
        // Initialize database and auth system
        Database db("assets.dat", "users.dat");
        AuthSystem auth(db);
        
        // Create and run GUI
        GUI gui(db, auth);
        gui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}