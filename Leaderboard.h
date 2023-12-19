#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
using namespace sf;
using namespace std;

class Leaderboard{
public:
    Leaderboard();
    Leaderboard(int row, int col, string username);
    void run();
    float width;
    float height;
    RenderWindow leaderboard;
    bool edited;

    Text header;
    Text ranking;
    string topScoresDisplay;
    vector<pair<string, string>> topScores;
    Font font;
    string username;
    void readFile();
    void loadFont();
    void setText();
    void positionText(Text &text, float x, float y, float scale);
    void drawText();
    void checkLeaderboard(const string& time);
    void createLeaderboard(const string currentUser);
    bool isOpen();
    int timeToSeconds(const string& time);
    void writeFile();

};
