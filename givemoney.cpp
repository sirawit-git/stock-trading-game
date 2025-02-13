#include <iostream>
#include <vector>
using namespace std;

struct Player {
    string name;
    int cash;
    int shares;
    int profit_loss;
};

vector<Player> initializePlayers(int numPlayers) {
    vector<Player> players;          
    int startMoney = 50000;  

    for (int i = 0; i < numPlayers; i++) {
        Player p;
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> p.name;
        p.cash = startMoney;
        p.shares = 0;
        p.profit_loss = 0;
        players.push_back(p);
    }

    return players;
}