#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
#include "Leaderboard.h"
#include <iostream>
#include <cctype>
#include <cmath>
#include <random>
using namespace sf;
using namespace std;

Board::Board(int rows, int columns, int mines, string userName): gameBoard(VideoMode((columns*32), (rows*32)+100), "Game Board") {
    this->mines = mines;
    minesDisplay = mines;
    width = columns*32;
    height = rows*32+100;
    totalRows = rows;
    totalCols = columns;
    paused = false;
    pauseMode = false;
    debug = false;
    gameState = "play";
    finalUsername = userName;
    Tiles.resize(rows, vector<Tile>(columns));
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            Tile newTile;
            newTile.setIndex(row, col);
            Tiles[row][col] = newTile;
        } }
    Digits.setTexture(digits);
    digitsMap = parseDigits(Digits);
    stopTimer = false;

    Face.setTexture(face_happy);
    Debug_Button.setTexture(debug_button);
    Pause_Play.setTexture(pause_button);
    Leaderboard_Button.setTexture(leaderboard_button);
    dig0.setTexture(digits);
    dig0.setTextureRect(IntRect(0, 0, 21, 32));
    dig1.setTexture(digits);
    dig1.setTextureRect(IntRect(21, 0, 21, 32));
    dig2.setTexture(digits);
    dig2.setTextureRect(IntRect(21*2, 0, 21, 32));
    dig3.setTexture(digits);
    dig3.setTextureRect(IntRect(21*3, 0, 21, 32));
    dig4.setTexture(digits);
    dig4.setTextureRect(IntRect(21*4, 0, 21, 32));
    dig5.setTexture(digits);
    dig5.setTextureRect(IntRect(21*5, 0, 21, 32));
    dig6.setTexture(digits);
    dig6.setTextureRect(IntRect(21*6, 0, 21, 32));
    dig7.setTexture(digits);
    dig7.setTextureRect(IntRect(21*7, 0, 21, 32));
    dig8.setTexture(digits);
    dig8.setTextureRect(IntRect(21*8, 0, 21, 32));
    dig9.setTexture(digits);
    dig9.setTextureRect(IntRect(21*9, 0, 21, 32));
    neg.setTexture(digits);
    neg.setTextureRect(IntRect(21*10, 0, 21, 32));

    assignMines(mines);
    createAdjacentTiles();
    assignValues();
    drawTiles();
    drawButtons();
    run();}

vector<vector<Tile>> Board::intializeBoard(){
    for (int row = 0; row < totalRows; row++) {
        for (int col = 0; col < totalCols; col++) {
            Tile newTile;
            newTile.setIndex(row, col);
            Tiles[row][col] = newTile;
        } }}

map<int, sf::Sprite> Board::parseDigits(sf::Sprite digits){
    map<int, sf::Sprite> digitsMap;

    for(int i = 0; i < 10; i++){
        sf::IntRect rect(i*21,0,21,32);
        digits.setTextureRect(rect);
        sf::Sprite sprite = digits;
        digitsMap.emplace(i, sprite);
    }

    return digitsMap;
}

int Board::assignMines(int mines){
    srand(time(nullptr));
    int minesPlaced = 0;
    while (minesPlaced < mines) {
        int randomRow = rand() % totalRows;
        int randomCol = rand() % totalCols;
        pair<int, int> position(randomCol, randomRow);
        if (!Tiles[randomRow][randomCol].hasMine) {
            Tiles[randomRow][randomCol].hasMine = true;
            Tiles[randomRow][randomCol].mineTile.setPosition(Vector2f(randomCol * 32, randomRow * 32));
            ++minesPlaced;
        } } }
void Board::drawMinesAndValues(){
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            if (Tiles[row][col].hasMine && Tiles[row][col].tileState == "revealed") {
                gameBoard.draw(Tiles[row][col].mineTile);
            }
            else if (Tiles[row][col].value != 0 && Tiles[row][col].tileState == "revealed" && !Tiles[row][col].hasMine) {
                gameBoard.draw(Tiles[row][col].valueSprite);
            }

        } }
}
void Board::debugMines(){
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            if (Tiles[row][col].hasMine) {
                gameBoard.draw(Tiles[row][col].mineTile);
            }
            else if (Tiles[row][col].value != 0 && Tiles[row][col].tileState == "revealed" && !Tiles[row][col].hasMine) {
                gameBoard.draw(Tiles[row][col].valueSprite);
            }
}}}
bool Board::tileExists(int targetRow, int targetCol) {
    // Check if the targetRow and targetCol are within the bounds of the Tiles array
    if (targetRow >= 0 && targetRow < Tiles.size() &&
        targetCol >= 0 && targetCol < Tiles[targetRow].size()) {
        return true;
    }
    return false;
}
void Board::createAdjacentTiles(){
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            //top left
            if (tileExists(row-1, col-1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row-1][col-1]); }
            //top center
            if (tileExists(row-1, col)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row-1][col]); }
            //top right
            if (tileExists(row-1, col+1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row-1][col+1]); }
            //direct left
            if (tileExists(row, col-1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row][col-1]); }
            //direct right
            if (tileExists(row, col+1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row][col+1]); }
            //bottom left
            if (tileExists(row+1, col-1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row+1][col-1]); }
            //bottom center
            if (tileExists(row+1, col)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row+1][col]); }
            //bottom right
            if (tileExists(row+1, col+1)) {
                Tiles[row][col].adjacentTiles.push_back(&Tiles[row+1][col+1]); }
        }}}
Texture& Board::getValueTexture(int num){
    if (num == 1)
        return txtManage.getTexture("number_1");
    else if (num == 2)
        return txtManage.getTexture("number_2");
    else if (num == 3)
        return txtManage.getTexture("number_3");
    else if (num == 4)
        return txtManage.getTexture("number_4");
    else if (num == 5)
        return txtManage.getTexture("number_5");
    else if (num == 6)
        return txtManage.getTexture("number_6");
    else if (num == 7)
        return txtManage.getTexture("number_7");
    else if (num == 8)
        return txtManage.getTexture("number_8");
}
void Board::assignValues(){
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            Tiles[row][col].value = 0;
            if (!Tiles[row][col].hasMine) {
                for (int i = 0; i < Tiles[row][col].adjacentTiles.size(); i++)
                    if (Tiles[row][col].adjacentTiles[i]->hasMine) {
                        Tiles[row][col].value++;}
                if (Tiles[row][col].value != 0) {
                    Tiles[row][col].valueSprite.setPosition(Vector2f(col * 32, row * 32));
                    Tiles[row][col].valueSprite.setTexture(getValueTexture(Tiles[row][col].value));
                    //cout << Tiles[row][col].value << endl;

                }}}}}


void Board::drawTiles() {
    if (!paused) {
        for (int row = 0; row < Tiles.size(); row++) {
            for (int col = 0; col < Tiles[row].size(); col++) {
                Tiles[row][col].sprite.setPosition(Vector2f(col*32, row*32));
                gameBoard.draw(Tiles[row][col].sprite);
        } } }
    if (paused) {
        for (int row = 0; row < Tiles.size(); row++) {
            for (int col = 0; col < Tiles[row].size(); col++) {
                Tiles[row][col].cover.setPosition(Vector2f(col*32, row*32));
                gameBoard.draw(Tiles[row][col].cover);}
        } } }
void Board::drawButtons() {
    Face.setPosition(Vector2f((totalCols/2*32)-32, 32*(totalRows+0.5)));
    gameBoard.draw(Face);
    Debug_Button.setPosition(Vector2f((totalCols*32)-304, 32*(totalRows+0.5)));
    gameBoard.draw(Debug_Button);
    Pause_Play.setPosition(Vector2f((totalCols*32)-240, 32*(totalRows+0.5)));
    gameBoard.draw(Pause_Play);
    Leaderboard_Button.setPosition(Vector2f((totalCols*32)-176, 32*(totalRows+0.5)));
    gameBoard.draw(Leaderboard_Button);
}
Sprite& Board::getCounterSprite(int num){
    if (num == 0)
        return dig0;
    else if (num == 1)
        return dig1;
    else if (num == 2)
        return dig2;
    else if (num == 3)
        return dig3;
    else if (num == 4)
        return dig4;
    else if (num == 5)
        return dig5;
    else if (num == 6)
        return dig6;
    else if (num == 7)
        return dig7;
    else if (num == 8)
        return dig8;
    else if (num == 9)
        return dig9;
}
void Board::Counter(int mineNum){
    bool isNegative = mineNum < 0;
    if (isNegative)
        mineNum = -mineNum;

    int digit3 = mineNum % 10;
    mineNum /= 10;
    int digit2 = mineNum % 10;
    mineNum /= 10;
    int digit1 = mineNum % 10;

    Sprite num3 = getCounterSprite(digit3);
    Sprite num2 = getCounterSprite(digit2);
    Sprite num1;
    if (isNegative)
        num1 = neg;
    else
        num1 = getCounterSprite(digit1);

    num3.setPosition(Vector2f(33+21+21, 32*(totalRows+0.5)+16));
    num2.setPosition(Vector2f(33+21, 32*(totalRows+0.5)+16));
    num1.setPosition(Vector2f(33, 32*(totalRows+0.5)+16));
    gameBoard.draw(num3);
    gameBoard.draw(num2);
    gameBoard.draw(num1);
}



void Board::Timer(){}




void Board::addFlag(int col, int row) {
    if (!paused) {
        Tiles[row][col].flagState = true;
        Tiles[row][col].flag.setTexture(flag);
        Tiles[row][col].flag.setPosition(Vector2f(col * 32, row * 32));
        minesDisplay--;
    }
}
void Board::removeFlag(int col, int row){
    if (!paused) {
        Tiles[row][col].flagState = false;
        minesDisplay++;
    }
}
void Board::checkFlag(int col, int row){
    if (Tiles[row][col].tileState == "hidden") {
        if (Tiles[row][col].flagState == true) {
            removeFlag(col, row);
        } else if (Tiles[row][col].flagState == false) {
            addFlag(col, row);
        }
    }
}
void Board::drawFlags() {
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            if (Tiles[row][col].flagState == true && Tiles[row][col].tileState == "hidden") {
                gameBoard.draw(Tiles[row][col].flag);
            } } } }

void Board::revealTile(int col, int row) {
    if (Tiles[row][col].tileState == "hidden" && Tiles[row][col].flagState == false) {
        Tiles[row][col].sprite.setTexture(tile_revealed);
        Tiles[row][col].tileState = "revealed";
        if (Tiles[row][col].value == 0) {
            for (int i = 0; i < Tiles[row][col].adjacentTiles.size(); i++) {
                if (!Tiles[row][col].adjacentTiles[i]->hasMine) {
                    revealTile(Tiles[row][col].adjacentTiles[i]->col, Tiles[row][col].adjacentTiles[i]->row);
                }
            }
        }
    }}

void Board::resetFunction(){
    // Reset game state variables
    paused = false;
    Pause_Play.setTexture(pause_button);
    debug = false;
    minesDisplay = mines;

    start_time = chrono::high_resolution_clock::now();
    elapsed_paused_time = 0;
    pauseTime = chrono::high_resolution_clock::now();

    // Clear and reinitialize Tiles vector
    Tiles.clear();
    Tiles.resize(totalRows, vector<Tile>(totalCols));

    // Reinitialize each Tile
    for (int row = 0; row < totalRows; row++) {
        for (int col = 0; col < totalCols; col++) {
            Tiles[row][col].setIndex(row, col);
            Tiles[row][col].resetTile(); // Assuming you have a method to reset each tile's state
            Tiles[row][col].sprite.setTexture(txtManage.getTexture("tile_hidden"));
        }
    }

    // Redistribute mines and recalculate adjacent tiles and values
    assignMines(mines);
    createAdjacentTiles();
    assignValues();

    // Reset any additional UI elements or game state as necessary
    // ...

    needsRedraw = true; // Flag to redraw the board
}

int Board::getRevealedTiles(){
    int numRevealed;
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            if (Tiles[row][col].tileState == "revealed") {
                numRevealed++; }}}
    return numRevealed;
}

void Board::checkGameLose(){
    for (int row = 0; row < Tiles.size(); row++) {
        for (int col = 0; col < Tiles[row].size(); col++) {
            if (Tiles[row][col].hasMine && Tiles[row][col].tileState == "revealed"){
                Face.setTexture(face_lose);
                gameState = "lose";
                stopTimer = true;
                needsRedraw = true;
                for (int row = 0; row < Tiles.size(); row++) {
                    for (int col = 0; col < Tiles[row].size(); col++) {
                        if (Tiles[row][col].hasMine)
                            Tiles[row][col].sprite.setTexture(tile_revealed);}}
            }}}}

void Board::checkGameWin(string time){
    if (getRevealedTiles() == ((totalRows*totalCols) - mines)) {
        stopTimer = true;
        Face.setTexture(face_win);
        gameState = "win";
        gameBoard.clear(Color::White);
        drawTiles();
        setWinFlags();
        drawButtons();
        Counter(minesDisplay);
        gameBoard.display();
    }
        if (gameState == "win") {
            leaderboard = new Leaderboard(totalRows, totalCols, finalUsername);

            leaderboard->checkLeaderboard(time);
            if (leaderboard->edited) {
                leaderboard->writeFile();
            }
            leaderboard->run();
        }
    }


void Board::setWinFlags(){
    if (gameState == "win") {
        for (int row = 0; row < Tiles.size(); row++) {
            for (int col = 0; col < Tiles[row].size(); col++){
                if (Tiles[row][col].hasMine && !Tiles[row][col].flagState){
                    addFlag(col, row);
                    gameBoard.draw(Tiles[row][col].flag);}
            }}}
}



void Board::run() {
    start_time = chrono::high_resolution_clock::now();
    elapsed_paused_time = 0;
    //auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
    pauseTime = chrono::high_resolution_clock::now();
    //int total_time = game_duration.count();
    pauseMode = false;

    while (gameBoard.isOpen()) {
        Event event;
        while (gameBoard.pollEvent(event)) {
            //press X button in top right-closes program, does not lead to game window
            if (event.type == Event::Closed) {
                gameBoard.close(); }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mousePosition = Mouse::getPosition(gameBoard);
                    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
                    //Reveal Tile
                    if (0 < event.mouseButton.y && event.mouseButton.y < height - 100 && !paused && gameState == "play") {
                        revealTile(floor(event.mouseButton.x/32), floor(event.mouseButton.y/32));
                        needsRedraw = true;
                        checkGameLose();
                        checkGameWin(endTime);
                    }
                    //Leaderboard Button
                    if (Leaderboard_Button.getGlobalBounds().contains(mousePosF)) {
                        if (!paused) {
                            paused = true;
                            Pause_Play.setTexture(play_button);
                            gameBoard.clear(Color::White);
                            drawTiles();
                            drawButtons();
                            Counter(minesDisplay);


                            if(!paused) {
                                //enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
                                if (pauseMode){
                                    auto pause_duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime);
                                    elapsed_paused_time += pause_duration.count();
                                }

                                auto current_time = chrono::high_resolution_clock::now();
                                auto game_duration = chrono::duration_cast<chrono::seconds>(current_time - start_time - chrono::seconds(elapsed_paused_time));
                                int total_time = game_duration.count();

                                if (total_time < 0) { total_time = 0; } // Correct negative time
                                minutes = total_time / 60;
                                seconds = total_time % 60;

                                pauseMode = false; // Reset pauseMode when unpaused
                            }
                            else {
                                if (!pauseMode) {
                                    pauseTime = chrono::high_resolution_clock::now(); // Capture pauseTime on pause session enter
                                    pauseMode = true;
                                }
                            }
                            int minutes0 = minutes / 10 % 10; //minutes index 0
                            int minutes1 = minutes % 10; // minutes index 1
                            int seconds0 = seconds / 10 % 10; // seconds index 0
                            int seconds1 = seconds % 10; // seconds index 1
                            //cout << minutes0 << minutes1 << seconds0 << seconds1 << endl;
                            endTime = to_string(minutes0) + to_string(minutes1) + ":" + to_string(seconds0) + to_string(seconds1);

                            Sprite min0 = getCounterSprite(minutes0);
                            min0.setPosition(Vector2f (totalCols*32 - 97, 32*(totalRows + 0.5f) + 16));
                            gameBoard.draw(min0);

                            Sprite min1 = getCounterSprite(minutes1);
                            min1.setPosition(Vector2f (totalCols*32 - 76, 32*(totalRows + 0.5f) + 16));
                            gameBoard.draw(min1);

                            Sprite sec0 = getCounterSprite(seconds0);
                            sec0.setPosition(Vector2f (totalCols*32 - 54, 32*(totalRows + 0.5f) + 16));
                            gameBoard.draw(sec0);

                            //Sprite sec1 = getCounterSprite(seconds1);
                            digitsMap[seconds1].setPosition(Vector2f (totalCols*32 - 33, 32*(totalRows + 0.5f) + 16));
                            gameBoard.draw(digitsMap[seconds1]);



                            gameBoard.display();
                            paused = false;
                        }
                        leaderboard = new Leaderboard(totalRows, totalCols, finalUsername);
                        leaderboard->run();


                        if (!paused) {
                            paused = false;
                            Pause_Play.setTexture(pause_button);
                        }
                        else {
                            Pause_Play.setTexture(play_button);
                            gameBoard.clear(Color::White);
                            drawTiles();
                            drawButtons();
                            Counter(minesDisplay);
                            gameBoard.display();
                        }
                        needsRedraw = true;}

                    //Pause and Play Button
                    if (Pause_Play.getGlobalBounds().contains(mousePosF) && gameState == "play") {
                        //cout << "game paused" << endl;
                        //PAUSING ACTION
                        if (!paused) {
                            Pause_Play.setTexture(play_button);
                            paused = true;}
                        //RESUMING ACTION
                        else if (paused) {
                            Pause_Play.setTexture(pause_button);
                            paused = false; }
                        needsRedraw = true; }
                    //Debug Button
                    if (Debug_Button.getGlobalBounds().contains(mousePosF)) {
                        if (debug == false) {
                            debug = true;}
                        else if (debug == true) {
                            debug = false;}
                        needsRedraw = true; }
                    //Reset Button
                    if (Face.getGlobalBounds().contains(mousePosF)) {
                        resetFunction();
                        Face.setTexture(face_happy);
                        gameState = "play";
                        needsRedraw = true;
                    }

                }
                //Set Flag
                if (event.mouseButton.button == Mouse::Right) {
                    if (0 < event.mouseButton.y < height - 100 && gameState == "play") {
                        checkFlag(floor(event.mouseButton.x/32), floor(event.mouseButton.y/32));
                        needsRedraw = true;
                    }
                }
            }

        }
        if(!paused && !stopTimer) {
            //enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
            if (pauseMode){
                auto pause_duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime);
                elapsed_paused_time += pause_duration.count();
            }

            auto current_time = chrono::high_resolution_clock::now();
            auto game_duration = chrono::duration_cast<chrono::seconds>(current_time - start_time - chrono::seconds(elapsed_paused_time));
            int total_time = game_duration.count();

            if (total_time < 0) { total_time = 0; } // Correct negative time
            minutes = total_time / 60;
            seconds = total_time % 60;

            pauseMode = false; // Reset pauseMode when unpaused
        }
        else {
            if (!pauseMode) {
                pauseTime = chrono::high_resolution_clock::now(); // Capture pauseTime on pause session enter
                pauseMode = true;
            }
        }
        int minutes0 = minutes / 10 % 10; //minutes index 0
        int minutes1 = minutes % 10; // minutes index 1
        int seconds0 = seconds / 10 % 10; // seconds index 0
        int seconds1 = seconds % 10; // seconds index 1
        //cout << minutes0 << minutes1 << seconds0 << seconds1 << endl;
        endTime = to_string(minutes0) + to_string(minutes1) + ":" + to_string(seconds0) + to_string(seconds1);




        //if (needsRedraw) {
            gameBoard.clear(Color::White);
            setWinFlags();
            drawTiles();
            drawButtons();
            if (!paused) {
                drawFlags();
                if (!debug)
                    drawMinesAndValues();
                else
                    debugMines();
                if (gameState == "lose")
                    debugMines();
            }

            Counter(minesDisplay);
            needsRedraw = false;

        Sprite min0 = getCounterSprite(minutes0);
        min0.setPosition(Vector2f (totalCols*32 - 97, 32*(totalRows + 0.5f) + 16));
        gameBoard.draw(min0);

        Sprite min1 = getCounterSprite(minutes1);
        min1.setPosition(Vector2f (totalCols*32 - 76, 32*(totalRows + 0.5f) + 16));
        gameBoard.draw(min1);

        Sprite sec0 = getCounterSprite(seconds0);
        sec0.setPosition(Vector2f (totalCols*32 - 54, 32*(totalRows + 0.5f) + 16));
        gameBoard.draw(sec0);

        //Sprite sec1 = getCounterSprite(seconds1);
        digitsMap[seconds1].setPosition(Vector2f (totalCols*32 - 33, 32*(totalRows + 0.5f) + 16));
        gameBoard.draw(digitsMap[seconds1]);

        gameBoard.display();

    }
}


//victory
    //mine tiles automatically flagged upon win-CHECK
    //can still check leaderboard
    //if winning time, displayed on leaderboard with *
//defeat
    //all mines are revealed-CHECK
    //pause play is inactive-CHECK
//timer
    //pause button pauses timer
    //leaderboard and face buttons work in pause mode
//leaderboard
    //pauses timer
    //make sure you cannot edit while leaerboard is up



    /*drawDigits
    set the time above the while lopp
    paused time variable whne paused

    durration
    total time*/