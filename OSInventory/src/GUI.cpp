#include "GUI.h"
#include "Database.h"
#include "AuthSystem.h"
#include "Asset.h"
#include "User.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <locale>


GUI::GUI(Database& db, AuthSystem& auth)
    : database(db),
    authSystem(auth),
    window(sf::VideoMode(1200, 800), "OS Inventory System"),
    currentEditingAsset(0, "", "", "", "", "", "", "", 0.0, "", "", "", ""),
    enteringUsername(true),
    darkMode(false)
{
    // Загрузка шрифта с проверкой пути
    std::string fontPath = "resources/Roboto-Regular.ttf";
    if (!mainFont.loadFromFile(fontPath)) {
        std::cerr << "Error: Failed to load font from path: " << fontPath << std::endl;

        namespace fs = std::filesystem;
        std::cerr << "Working directory: " << fs::current_path().string() << std::endl;

        fontPath = "C:/Users/ivashkevichie_a/Documents/Testing/OSInventory/resources/Roboto-Regular.ttf";
        if (!mainFont.loadFromFile(fontPath)) {
            std::cerr << "Error: Failed to load font from absolute path: " << fontPath << std::endl;
            mainFont = sf::Font();
        }
    }

    currentState = AppState::LOGIN;
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
        sf::sleep(sf::milliseconds(16));  // ~60 FPS
    }
}

void GUI::update() {
    // Реализация метода update
}

void GUI::handleMouseClick(int x, int y) {
    sf::Vector2f mousePos(static_cast<float>(x), static_cast<float>(y));

    if (currentState == AppState::LOGIN) {
        // Проверка клика по кнопке Login
        if (loginButton.getGlobalBounds().contains(mousePos)) {
            // Обработка логина
        }
    }
    // Добавьте обработку для других состояний
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // Обработка закрытия окна
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Обработка кликов мыши
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        // Обработка ввода текста
        if (currentState == AppState::LOGIN) {
            if (event.type == sf::Event::TextEntered) {
                handleTextInput(event.text);
            }
        }
    } // Добавлена закрывающая скобка для метода handleEvents
}

// Перенесено изнутри другого метода
void GUI::handleTextInput(const sf::Event::TextEvent& textEvent) {
    if (textEvent.unicode == '\t') { // Tab для переключения между полями
        enteringUsername = !enteringUsername;
    }
    else if (textEvent.unicode == '\b') { // Backspace
        if (enteringUsername && !username.empty()) {
            username.pop_back();
        }
        else if (!enteringUsername && !password.empty()) {
            password.pop_back();
        }
    }
    else if (textEvent.unicode < 128) { // Обычные символы
        if (enteringUsername) {
            username += static_cast<char>(textEvent.unicode);
        }
        else {
            password += static_cast<char>(textEvent.unicode);
        }
    }
}

void GUI::render() {
    window.clear(getBackgroundColor());

    switch (currentState) {
    case AppState::LOGIN: renderLogin(); break;
    case AppState::MAIN_MENU: renderMainMenu(); break;
    case AppState::VIEW_ASSETS: renderViewAssets(); break;
    case AppState::ADD_ASSET: renderAddAsset(); break;
    case AppState::EDIT_ASSET: renderEditAsset(); break;
    case AppState::SEARCH_ASSETS: renderSearchAssets(); break;
    case AppState::USER_MANAGEMENT: renderUserManagement(); break;
    case AppState::SETTINGS: renderSettings(); break;
    }

    window.display();
}

void GUI::renderLogin() {
    window.clear(sf::Color::White);

    // Заголовок системы
    sf::Text title(L"HG Инициализация ОИТ", mainFont, 36);
    title.setFillColor(getPrimaryColor());
    title.setPosition(100, 100);
    window.draw(title);
	
	// Подпись поля логина
	sf::Text loginLabel("Логин", mainFont, 20);
	loginLabel.setPosition(100, 170); 
	window.draw(loginLabel);
	
    // Поле ввода имени пользователя
	usernameField.setSize(sf::Vector2f(400, 40));
	usernameField.setPosition(100, 200);
	if (enteringUsername) {
		usernameField.setOutlineColor(sf::Color::Blue); // Активное поле
	} else {
		usernameField.setOutlineColor(sf::Color(200, 200, 200)); // Неактивное
	}
	
	// Placeholder для логина
	if (username.empty()) {
		sf::Text placeholder("Введите логин", mainFont, 18);
		placeholder.setFillColor(sf::Color(150, 150, 150));
		placeholder.setPosition(110, 210);
		window.draw(placeholder);
	}
	
    // Текст логина
    usernameText.setFont(mainFont);
    usernameText.setString(username);
    usernameText.setCharacterSize(20);
    usernameText.setFillColor(sf::Color::Black);
    usernameText.setPosition(110, 210);
    window.draw(usernameText);

    // Подпись поля пароля
    sf::Text passwordLabel(L"Пароль:", mainFont, 20);
    passwordLabel.setFillColor(sf::Color::Black);
    passwordLabel.setPosition(100, 250);
    window.draw(passwordLabel);

    // Поле ввода пароля
    sf::RectangleShape passwordField(sf::Vector2f(400, 50));
    passwordField.setPosition(100, 280);
    passwordField.setFillColor(sf::Color::White);
    passwordField.setOutlineThickness(2);
    passwordField.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(passwordField);

    // Текст пароля
    passwordText.setFont(mainFont);
    passwordText.setString(std::string(password.size(), '*'));
    passwordText.setCharacterSize(20);
    passwordText.setFillColor(sf::Color::Black);
    passwordText.setPosition(110, 290);
    window.draw(passwordText);

    // Кнопка входа
    loginButton.setSize(sf::Vector2f(400, 50));
    loginButton.setPosition(100, 380);
    loginButton.setFillColor((!username.empty() && !password.empty()) 
    ? sf::Color(70, 130, 180)  // Активный синий
    : sf::Color(150, 150, 150)); // Неактивный серый

    // Курсор ввода
    if (enteringUsername) {
        if (this->cursorClock.getElapsedTime().asSeconds() < 0.5f) {
            sf::RectangleShape cursor(sf::Vector2f(2, 20));
            cursor.setPosition(110 + usernameText.getLocalBounds().width, 210);
            cursor.setFillColor(sf::Color::Black);
            window.draw(cursor);
        }
        else if (this->cursorClock.getElapsedTime().asSeconds() > 1.0f) {
            this->cursorClock.restart();
        }
    }

    // Placeholder для логина
    if (username.empty()) {
        sf::Text placeholder(L"Логин", mainFont, 20);
        placeholder.setFillColor(sf::Color(150, 150, 150));
        placeholder.setPosition(110, 210);
        window.draw(placeholder);
    }

    // Текст на кнопке
    sf::Text loginText(L"Войти", mainFont, 24);
    loginText.setFillColor(sf::Color::White);
    loginText.setPosition(
        loginButton.getPosition().x + loginButton.getSize().x / 2 - loginText.getLocalBounds().width / 2,
        loginButton.getPosition().y + loginText.getLocalBounds().height / 2
    );
    window.draw(loginText);

    // Обработка клика по кнопке
    if (loginButton.getGlobalBounds().contains(
        static_cast<float>(sf::Mouse::getPosition(window).x),
        static_cast<float>(sf::Mouse::getPosition(window).y))) {
        loginButton.setOutlineThickness(2);
        loginButton.setOutlineColor(sf::Color::White);
    }

    window.draw(loginButton);
}

void GUI::renderMainMenu() {
    window.clear(getBackgroundColor());

    const User* user = authSystem.getCurrentUser();

    // Приветствие
    sf::Text welcomeText("Welcome, " + user->getFullName(), mainFont, 32);
    welcomeText.setFillColor(getPrimaryColor());
    welcomeText.setPosition(50, 50);
    window.draw(welcomeText);

    // Кнопки меню
    float y = 150;
    std::vector<std::string> buttons = { "View Assets", "Add New Asset", "Search Assets", "User Management", "Settings", "Logout" };

    for (const auto& buttonText : buttons) {
        // Пропускаем кнопки, которые не должны отображаться для текущего пользователя
        if (buttonText == "Add New Asset" && !(user->isEditor() || user->isAdmin())) continue;
        if (buttonText == "User Management" && !user->isAdmin()) continue;

        sf::RectangleShape button(sf::Vector2f(300, 60));
        button.setPosition(100, y);
        button.setFillColor(getSecondaryColor());

        if (button.getGlobalBounds().contains(
            static_cast<float>(sf::Mouse::getPosition(window).x),
            static_cast<float>(sf::Mouse::getPosition(window).y))) {
            button.setOutlineThickness(2);
            button.setOutlineColor(sf::Color::White);
        }

        window.draw(button);

        sf::Text text(buttonText, mainFont, 24);
        text.setFillColor(getTextColor());
        text.setPosition(
            button.getPosition().x + button.getSize().x / 2 - text.getLocalBounds().width / 2,
            button.getPosition().y + text.getLocalBounds().height / 2
        );
        window.draw(text);

        y += 80;
    }
}

void GUI::renderViewAssets() {
    // Реализация renderViewAssets
}

void GUI::renderAddAsset() {
    // Реализация renderAddAsset
}

void GUI::renderEditAsset() {
    // Реализация renderEditAsset
}

void GUI::renderSearchAssets() {
    // Реализация renderSearchAssets
}

void GUI::renderUserManagement() {
    // Реализация renderUserManagement
}

void GUI::renderSettings() {
    // Реализация renderSettings
}

bool GUI::createInputField(const sf::FloatRect& bounds, std::string& content,
    const std::string& placeholder, bool isPassword) {
    // Реализация createInputField
    return false;
}

void GUI::createLabel(const sf::FloatRect& bounds, const std::string& text,
    const sf::Color& color, unsigned int fontSize) {
    // Реализация createLabel
}

sf::Color GUI::getBackgroundColor() const {
    return darkMode ? sf::Color(30, 30, 30) : sf::Color(240, 240, 240);
}

sf::Color GUI::getTextColor() const {
    return darkMode ? sf::Color::White : sf::Color::Black;
}

sf::Color GUI::getPrimaryColor() const {
    return darkMode ? sf::Color(65, 105, 225) : sf::Color(70, 130, 180);
}

sf::Color GUI::getSecondaryColor() const {
    return darkMode ? sf::Color(100, 100, 100) : sf::Color(200, 200, 200);
}

bool GUI::createButton(const sf::FloatRect& bounds, const std::string& text,
    const sf::Color& color, const sf::Color& textColor) {
    static sf::RectangleShape button;
    static sf::Text buttonText;

    button.setPosition(bounds.left, bounds.top);
    button.setSize({ bounds.width, bounds.height });
    button.setFillColor(color);

    buttonText.setFont(mainFont);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(textColor);

    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(bounds.left + bounds.width / 2.0f,
        bounds.top + bounds.height / 2.0f);

    window.draw(button);
    window.draw(buttonText);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::White);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            return true;
        }
    }
    else {
        button.setOutlineThickness(0);
    }

    return false;
}
