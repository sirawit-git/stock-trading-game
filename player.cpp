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

string getTitle(const Player& player) {

    int highRiskTrades = 0, lowRiskTrades = 0, lossTrades = 0;
    int totalTrades = player.trades.size();
    double maxLoss = 0, totalProfit = player.cash + (player.shares * 500) - player.startingMoney;
    double cashRatio = player.cash / player.startingMoney;

    for (double trade : player.trades) {
        if (trade >= 6000) highRiskTrades++;
        if (trade < 3000) lowRiskTrades++;
        if (trade < 0) {
            lossTrades++;
            if (-trade > maxLoss) maxLoss = -trade;
        }
    }

    if (player.cash > 150000) return "เศรษฐีใหม่";
    if (totalProfit >= player.startingMoney) return "พ่อค้าเลือดเย็น";
    if (highRiskTrades > totalTrades / 2) return "นักเสี่ยงดวง";
    if (lowRiskTrades == totalTrades) return "ปลอดภัยไว้ก่อน";
    if (cashRatio >= 0.7) return "สายเก็บออม";
    if (lossTrades > 0 && player.cash > player.startingMoney) return "นักลงทุนสายถึก";
    if (player.cash < 5000) return "จากดาดฟ้าสู่ดิน";
    if (maxLoss >= player.startingMoney * 0.5) return "หมดตัวเพราะไม้เดียว";
    if (lossTrades > totalTrades / 2) return "เจ้าพ่อดวงเกลือ";

    return "นักเทรดทั่วไป";
}