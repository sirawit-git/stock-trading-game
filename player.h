#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Player {  // ต้องประกาศ struct Player ก่อน
    string name;
    double cash;
    int shares;
    double profit_loss;
    double startingMoney;
    vector<double> trades;
};

// ประกาศฟังก์ชันที่ใช้ Player
void SetConsoleColor(int color);
void DrawWinnerBanner(const string& winnerName, int color);
void DrawrankPlayers(vector<Player>& players);

vector<Player> initializePlayers(int numPlayers); // Function to create players
void randMoney(vector<Player>& players); // Function to randomize money
void displayVictory(const vector<Player> &players);
void rankPlayers(vector<Player>& players);
string getTitle(const Player& player); // Function to get player's title

#endif