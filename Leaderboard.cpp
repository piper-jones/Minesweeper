#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "Leaderboard.h"
using namespace sf;
using namespace std;

Leaderboard::Leaderboard(){}

Leaderboard::Leaderboard(int row, int col, string username): leaderboard(VideoMode(col*16, (row*16)+50), "Leaderboard") {
    width = col * 16;
    height = row * 16 + 50;
    edited = false;
    this->username = username;
    loadFont();
    readFile();
}

void Leaderboard::readFile() {
    ifstream rank("files/leaderboard.txt");
    string singleLine;
    vector<pair<string, string>> users;
    while(getline(rank, singleLine)) {
        istringstream stream(singleLine);
        string time;
        string user;
        getline(stream, time, ',');
        getline(stream, user);
        users.push_back(make_pair(time, user));
    }
    rank.close();
    topScores = users;
}


void Leaderboard::loadFont() {
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Failed to load font" << endl;
    } }

void Leaderboard::positionText(Text &text, float x, float y, float scale) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(Vector2f((x/2), (y/2 - scale))); }

void Leaderboard::setText() {
    header.setFont(font);
    header.setString("LEADERBOARD");
    header.setCharacterSize(20);
    header.setFillColor(Color::White);
    header.setStyle(Text::Bold | Text::Underlined);

    ranking.setFont(font);
    ranking.setString(topScoresDisplay);
    ranking.setCharacterSize(18);
    ranking.setFillColor(Color::White);
    ranking.setStyle(Text::Bold);

    positionText(header, width, height, 120);
    positionText(ranking, width, height, -20); }

void Leaderboard::drawText() {
    leaderboard.draw(header);
    leaderboard.draw(ranking);     }

bool Leaderboard::isOpen(){
    if (leaderboard.isOpen())
        return true;
    else
        return false;
}

void Leaderboard::run() {
    while (leaderboard.isOpen()) {
        Event event;
        while (leaderboard.pollEvent(event)) {
            if (event.type == Event::Closed)
                leaderboard.close(); }
        leaderboard.clear(Color::Blue);
        //checkLeaderboard();
        createLeaderboard(username);
        setText();
        drawText();
        leaderboard.display(); } }



//takes in users score if they win and adjusts the vector of top 5 users if needed
int Leaderboard::timeToSeconds(const string& time) {
    int minutes = std::stoi(time.substr(0, 2));
    int seconds = std::stoi(time.substr(3, 2));
    return minutes * 60 + seconds;
}

void Leaderboard::checkLeaderboard(const string& time) {
    int newTimeInSeconds = timeToSeconds(time);

    for (int i = 0; i < topScores.size(); ++i) {
        int currentTimeInSeconds = timeToSeconds(topScores[i].first);

        if (newTimeInSeconds < currentTimeInSeconds) {
            topScores.insert(topScores.begin() + i, std::make_pair(time, username));
            edited = true;

            // Ensure the list size does not exceed 5
            if (topScores.size() > 5) {
                topScores.pop_back();
            }
            return;
        }
    }
}

void Leaderboard::writeFile() {
    ofstream file("files/leaderboard.txt");

    for (auto & topScore : topScores) {
        file << topScore.first << "," << topScore.second << std::endl;
    }

    file.close();
}

    //if compare score
    //iterate through vector and if it is greater than anything in rank replace that item and push back everything else one index
    //THEN WRITE THE NEW VECTOR TO THE FILE?????????
    //user vector[i].first to get score
    //use vector[i].second to get user
    //in for loop only iterate up to certain #

    //assign string youve created to the string that is the leaderboard


//takes whatever the current vector of winners is and makes it into a string and assigns the string
void Leaderboard::createLeaderboard(const string currentUser) {
    topScoresDisplay = "";
    for (int i = 0; i < topScores.size(); i++) {
        string num = to_string(i+1);
        if (topScores[i].second == currentUser)
            topScoresDisplay += num + ".\t" + topScores[i].first + "\t" + topScores[i].second + "*\n\n";
        else
            topScoresDisplay += num + ".\t" + topScores[i].first + "\t" + topScores[i].second + "\n\n";
    }}

    //in run, call get top scores to make sure the vector is accurate of the top 5 players
    //if current_user == vector[i], add * to their name in the string

    //call this everytime you display the leaderboard so it is always consistent with and without the star
