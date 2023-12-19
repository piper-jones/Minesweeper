#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
using namespace sf;
using namespace std;
#include <iostream>
#include <cctype>

WelcomeWindow::WelcomeWindow(int row, int col): welcome(VideoMode((col*32), (row*32)+100), "Welcome Window") {
    width = col * 32;
    height = row * 32 + 100;
    displayName = "";
    Enter = false;
    loadFont();
    run(); }


void WelcomeWindow::loadFont() {
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load font" << endl;
    } }

void WelcomeWindow::positionText(Text &text, float x, float y, float scale) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(Vector2f((x/2), (y/2 - scale))); }

void WelcomeWindow::setText() {
    welcomeTxt.setFont(font);
    welcomeTxt.setString("WELCOME TO MINESWEEPER!");
    welcomeTxt.setCharacterSize(24);
    welcomeTxt.setFillColor(Color::White);
    welcomeTxt.setStyle(Text::Bold | Text::Underlined);

    enterName.setFont(font);
    enterName.setString("Enter your name:");
    enterName.setCharacterSize(20);
    enterName.setFillColor(Color::White);
    enterName.setStyle(Text::Bold);

    userName.setFont(font);
    userName.setString(displayName + "|");
    userName.setCharacterSize(18);
    userName.setFillColor(Color::Yellow);
    userName.setStyle(Text::Bold);

    positionText(welcomeTxt, width, height, 150);
    positionText(enterName, width, height, 75);
    positionText(userName, width, height, 45); }


void WelcomeWindow::drawText() {
    welcome.draw(welcomeTxt);
    welcome.draw(enterName);
    welcome.draw(userName);
    }

void WelcomeWindow::run() {
    while (welcome.isOpen()) {
        Event event;
        while (welcome.pollEvent(event)) {
            //press X button in top right-closes program, does not lead to game window
            if (event.type == Event::Closed) {
                welcome.close(); }
            if (event.type == Event::TextEntered) {
                redraw = true;
                // Only letters
                if (65 <= event.text.unicode && event.text.unicode <= 90
                || 97 <= event.text.unicode && event.text.unicode <= 120) {
                    if (displayName.empty()) { //changes first to uppercase
                        displayName += toupper(static_cast<char>(event.text.unicode)); }
                    else if (!displayName.empty() && displayName.size() < 10) { //changes the rest to lowercase
                        displayName += tolower(static_cast<char>(event.text.unicode)); }
                }
                // Backspace
                else if (event.text.unicode == 8) {
                    if (!displayName.empty()) {
                        displayName.pop_back();} }
                //Enter key-continues to Game window
                else if (event.text.unicode == 13) {
                    finalUserName = displayName;
                    if (!displayName.empty()) {
                        welcome.close();
                    }
                    Enter = true;
                }
            }
        }
        if (redraw) {
            welcome.clear(Color::Blue);
            setText();  // Update the text object with 'displayName'
            drawText(); // Draw the updated text object
            welcome.display();
            redraw = false;
        }

    }
}

