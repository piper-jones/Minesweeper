#include <iostream>
#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "Leaderboard.h"
#include "gui.h"
#include "Board.h"
#include <string>
using namespace std;



int main() {
    readDimensions();
    WelcomeWindow welcomeWindow(rowCount, colCount);
    welcomeWindow.run();
    string userName;
    userName += toupper(static_cast<unsigned char>(welcomeWindow.finalUserName[0]));

    for (size_t i = 1; i < welcomeWindow.finalUserName.length(); ++i) {
        userName += tolower(static_cast<unsigned char>(welcomeWindow.finalUserName[i]));
    }

if (welcomeWindow.Enter == true)
       Board gameWindow(rowCount, colCount, mines, userName);





    return 0;
}