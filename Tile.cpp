#include <string>
#include "Tile.h"
#include "TextureManager.h"

Tile::Tile() {
    value = 0;
    tileState = "hidden";
    flagState = false;
    hasMine = false;
    sprite.setTexture(txtM.getTexture("tile_hidden"));
    cover.setTexture(txtM.getTexture("tile_revealed"));
    mineTile.setTexture(txtM.getTexture("mine"));
}

string Tile::getState(){
    return tileState;
}
//revealed or unrevealed, returns
int Tile::checkValue(){
    return value;
}

void Tile::setIndex(int r, int c){
    row = r;
    col = c;
}


Tile Tile::operator=(const Tile& rhs) {
    if (this != &rhs) {
        row = rhs.row;
        col = rhs.col;
        value = rhs.value;
        tileState = rhs.tileState;
        sprite = rhs.sprite;
    }
    return *this;
}

void Tile::resetTile(){
    value = 0;               // Reset the value of the tile
    tileState = "hidden";    // Reset the state to hidden
    flagState = false;       // Reset the flag state
    hasMine = false;         // Ensure the tile does not have a mine

    // Reset textures to their initial states
    sprite.setTexture(txtM.getTexture("tile_hidden"));
}
