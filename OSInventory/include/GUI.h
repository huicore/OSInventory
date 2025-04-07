#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Database.h"
#include "AuthSystem.h"

class GUI {
public:
    GUI(Database& db, AuthSystem& auth);
    void run();
    void handleTextInput(const sf::Event::TextEvent& textEvent);

private:
    // Состояния приложения
    enum class AppState {
        LOGIN,
        MAIN_MENU,
        VIEW_ASSETS,
        ADD_ASSET,
        EDIT_ASSET,
        SEARCH_ASSETS,
        USER_MANAGEMENT,
        SETTINGS
    };

    // Члены класса
    Database& database;
    AuthSystem& authSystem;
    sf::RenderWindow window;
	sf::Clock cursorClock;
    sf::Font mainFont;
	sf::Text usernameText;
    sf::Text passwordText;
	sf::RectangleShape usernameField;
    AppState currentState;
    bool darkMode;
    Asset currentEditingAsset;
    std::string username;
    std::string password;
    bool enteringUsername; // Флаг для переключения между полями

    // Графические элементы
    sf::RectangleShape loginButton;

    // Методы
    void update();
    void handleEvents();
    void handleMouseClick(int x, int y);
    void handleLoginEvents(sf::Event& event);
    void handleMainMenuEvents(sf::Event& event);
    void render();
    void renderLogin();
    void renderMainMenu();
    void renderViewAssets();
    void renderAddAsset();
    void renderEditAsset();
    void renderSearchAssets();
    void renderUserManagement();
    void renderSettings();
    bool createInputField(const sf::FloatRect& bounds, std::string& content,
        const std::string& placeholder, bool isPassword = false);
    void createLabel(const sf::FloatRect& bounds, const std::string& text,
        const sf::Color& color, unsigned int fontSize = 20);
    sf::Color getBackgroundColor() const;
    sf::Color getTextColor() const;
    sf::Color getPrimaryColor() const;
    sf::Color getSecondaryColor() const;
    bool createButton(const sf::FloatRect& bounds, const std::string& text,
        const sf::Color& color, const sf::Color& textColor);
};