#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class WelcomeWindow{
public:
    WelcomeWindow(int row, int col);
    void run();
    string finalUserName;
    bool Enter;
    bool redraw = true;
private:
    RenderWindow welcome;
    float width;
    float height;
    Text welcomeTxt;
    Text enterName;
    Text userName;
    string displayName;
    Font font;
    void loadFont();
    void setText();
    void positionText(Text &text, float x, float y, float scale);
    void drawText();
};
