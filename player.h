#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Player {
    string name;
    int cash;
    int shares;
    int profit_loss;
};

vector<Player> initializePlayers(int numPlayers); // Function to create players
void randMoney(vector<Player>& players); // Function to randomize money

#endif
