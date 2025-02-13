#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Player {
    string name;
    int cash;
    int shares;
    int profit_loss;
};

extern vector<Player> initializePlayers(int numPlayers); // ประกาศ extern

void displayStatus(const vector<Player>& players, int stockPrice) {
    cout << "\n--- Current Status ---\n";
    cout << "Stock Price: " << stockPrice << " Baht\n";
    for (const auto& player : players) {
        cout << player.name << " | Cash: " << player.cash << " | Shares: " << player.shares
             << " | Profit/Loss: " << player.profit_loss << "\n";
    }
    cout << "----------------------\n";
}

string generateMarketNews() {
    vector<string> news = {
        "Good earnings report boosts stocks!",
        "Economic downturn causes market panic!",
        "Government announces stimulus package!",
        "Interest rates increase, impacting stocks!",
        "Tech sector boom pushes stock prices higher!"
    };
    return news[rand() % news.size()];
}

void playerTurn(Player& player, int& stockPrice) {
    int choice, amount;
    cout << "\n" << player.name << ", what would you like to do?\n";
    cout << "1. Buy Shares\n2. Sell Shares\n3. Skip Turn\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {  // Buy Shares
        cout << "How many shares would you like to buy? (Stock price: " << stockPrice << "): ";
        cin >> amount;
        int cost = amount * stockPrice;
        if (cost > player.cash) {
            cout << "Not enough cash!\n";
        } else {
            player.cash -= cost;
            player.shares += amount;
        }
    } else if (choice == 2) {  // Sell Shares
        cout << "How many shares would you like to sell? (Stock price: " << stockPrice << "): ";
        cin >> amount;
        if (amount > player.shares) {
            cout << "Not enough shares!\n";
        } else {
            int revenue = amount * stockPrice;
            player.cash += revenue;
            player.shares -= amount;
        }
    }
}

int main() {
    srand(time(0));

    int numPlayers;
    cout << "Number of players (3-5): ";
    cin >> numPlayers;
    if (numPlayers < 3 || numPlayers > 5) {
        cout << "Players must be between 3-5.\n";
        return 1;
    }

    vector<Player> players = initializePlayers(numPlayers);  // ใช้ฟังก์ชันนี้แทนการสร้าง players เอง

    int stockPrice = 500;
    int rounds = 5;

    for (int round = 1; round <= rounds; ++round) {
        cout << "\n=== Round " << round << " ===\n";
        cout << "Market News: " << generateMarketNews() << "\n";
        displayStatus(players, stockPrice);

        for (auto& player : players) {
            playerTurn(player, stockPrice);
        }

        int change = (rand() % 21) - 10;
        stockPrice += (stockPrice * change) / 100;
        if (stockPrice < 1) stockPrice = 1;

        for (auto& player : players) {
            int totalValue = player.shares * stockPrice;
            player.profit_loss = totalValue + player.cash - 50000; // ต้องใช้เงินเริ่มต้น 50000 แทน 10000
        }
    }

    cout << "\n=== Game Over! ===\n";
    displayStatus(players, stockPrice);
    return 0;
}
