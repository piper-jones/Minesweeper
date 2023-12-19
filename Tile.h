#pragma once
#include <string>
#include <vector>
using namespace std;
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Tile {
public:
    Tile();
    string tileState;
    bool flagState;
    bool hasMine;
    int value;
    int row;
    int col;
    sf::Sprite sprite;
    TextureManager txtM;
    sf::Sprite flag;
    vector<Tile*> adjacentTiles;
    sf::Sprite cover;
    sf::Sprite mineTile;
    sf:: Sprite valueSprite;


    string getState();
    //revealed or unrevealed, returns
    int checkValue();
    void setIndex(int r, int c);
    Tile operator=(const Tile& rhs);
    void resetTile();
};
