#include "player.h"
#include <iostream>

using namespace std;

vector<Player> initializePlayers(int numPlayers) {
    vector<Player> players;  
    int startMoney = 50000;  

    for (int i = 0; i < numPlayers; i++) {
        Player p;  
        cout << "Enter name for player " << i + 1 << ": ";
        cin.ignore();
        getline(cin,p.name);
        p.cash = startMoney;
        p.shares = 0;
        p.profit_loss = 0;
        players.push_back(p);
    }

    return players;
}

void randMoney(vector<Player>& players) {
    int amounts[] = {1000, 2000, -1000, -2000, 5000, 3000, 4000, -2000, 4600, -3000, 5600, 4000, -3440, 1000};
    int numAmounts = sizeof(amounts) / sizeof(amounts[0]);

    srand(time(0));

    for (size_t i = 0; i < players.size(); i++) {
        int randomMoney = amounts[rand() % numAmounts];
        players[i].cash += randomMoney;
        cout << players[i].name << " gets: " << randomMoney << " baht"
             << "| Remaining money : " << players[i].cash << " baht\n";
    }
}
