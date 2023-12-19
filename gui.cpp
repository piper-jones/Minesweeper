#include <SFML/Graphics/Font.hpp>
#include <fstream>
#include <sstream>
using namespace std;
using namespace sf;
#include "gui.h"

int colCount;
int rowCount;
int mines;


void readDimensions() {
    ifstream config("files/config.cfg");
    string singleLine;

    if (config.is_open()) {

        getline(config, singleLine);
        colCount = stoi(singleLine);

        getline(config, singleLine);
        rowCount = stoi(singleLine);

        getline(config, singleLine);
        mines = stoi(singleLine);

        config.close();
    }
}



