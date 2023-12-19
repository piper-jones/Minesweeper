#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cctype>
#include "Tile.h"
#include "TextureManager.h"
#include <random>
#include <chrono>
#include <map>
#include "Leaderboard.h"
using namespace sf;


class Board {
public:
    Leaderboard* leaderboard;

    map<int, sf::Sprite> parseDigits(sf::Sprite digits);
    void setWinFlags();
    int minutes;
    int seconds;
    map<int, sf::Sprite> digitsMap;
    int total_time;


    //Class Construction
    RenderWindow gameBoard;
    Board(int row, int col, int mines, string userName);
    void run();
    TextureManager txtManage;
    vector<vector<Tile>> Tiles;
    int mines;
    unsigned int minesDisplay;
    int width;
    int height;
    int totalRows;
    int totalCols;
    vector<Sprite> flagList;
    mt19937 random_mt;
    bool paused;
    bool pauseMode;
    bool debug;
    string gameState;
    string finalUsername;

    //textures
    Texture tile_revealed = txtManage.getTexture("tile_revealed");
    Texture mine = txtManage.getTexture("mine");
    Sprite Mine;
    Texture digits = txtManage.getTexture("digits");
    Sprite Digits;
    Sprite dig0;
    Sprite dig1;
    Sprite dig2;
    Sprite dig3;
    Sprite dig4;
    Sprite dig5;
    Sprite dig6;
    Sprite dig7;
    Sprite dig8;
    Sprite dig9;
    Sprite neg;
    Texture face_happy = txtManage.getTexture("face_happy");
    Texture face_win = txtManage.getTexture("face_win");
    Texture face_lose = txtManage.getTexture("face_lose");
    Sprite Face;
    Texture debug_button = txtManage.getTexture("debug");
    Sprite Debug_Button;
    Texture pause_button = txtManage.getTexture("pause");
    Texture play_button = txtManage.getTexture("play");
    Sprite Pause_Play;
    Texture leaderboard_button = txtManage.getTexture("leaderboard");
    Sprite Leaderboard_Button;
    Texture flag = txtManage.getTexture("flag");
    Sprite Flag;


    //Board Initialization
    vector<vector<Tile>> intializeBoard();
    bool needsRedraw = true;
    void drawTiles();
    vector<vector<Tile>> generateBoard();
    void drawButtons();
    Sprite& getCounterSprite(int num);
    void Counter(int mineNum);
    void Timer();
    void addFlag(int col, int row);
    void removeFlag(int col, int row);
    void checkFlag(int col, int row);
    void drawFlags();
    bool tileExists(int targetRow, int targetCol);
    void createAdjacentTiles();
    Texture& getValueTexture(int num);
    void assignValues();
    void debugMines();
    void checkGameLose();
    void checkGameWin(string time);
    int getRevealedTiles();
    string endTime;
    bool stopTimer;
    chrono::time_point<chrono::high_resolution_clock> start_time;
    int elapsed_paused_time;
    chrono::time_point<chrono::high_resolution_clock> pauseTime;

    //make board, fill board, add mines, etc
    int assignMines(int mines);
    void drawMinesAndValues();

    void revealTile(int row, int col);
    void resetFunction();
};



