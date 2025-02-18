#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>
#include "player.h"
#include "graph.h"

using namespace std;

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
    vector<string> news;
    ifstream file("news.txt"); // เปิดไฟล์ news.txt
    string line;

    if (!file) {
        cerr << "Error: Cannot open news.txt!\n";
        return "No news available.";
    }

    while (getline(file, line)) {
        if (!line.empty()) news.push_back(line);
    }
    
    file.close();

    if (news.empty()) return "No news available.";

    return news[rand() % news.size()];
}

void playerTurn(Player& player, int& stockPrice) {
    int choice, amount;
    cout << "\n" << player.name << ", what would you like to do?\n";
    cout << "1. Buy Shares\n2. Sell Shares\n3. Skip Turn\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {  // Buy Shares

        do{
            cout << "How many shares would you like to buy? (Stock price: " << stockPrice << "): ";
            cin >> amount;
            int cost = amount*stockPrice;
            if (cost > player.cash) {
                cout << "Not enough cash!\n";
            }
        } while ((amount*stockPrice) > player.cash);
            int cost = amount*stockPrice;
            player.cash -= cost;
            player.shares += amount;
            player.trades.push_back(-cost);
    } else if (choice == 2) {  // Sell Shares
        cout << "How many shares would you like to sell? (Stock price: " << stockPrice << "): ";
        cin >> amount;
        if (amount > player.shares) {
            cout << "Not enough shares!\n";
        } else {
            int revenue = amount * stockPrice;
            player.cash += revenue;
            player.shares -= amount;
            player.trades.push_back(revenue);
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

    vector<Player> players = initializePlayers(numPlayers);

    cout << "\n=== Randomizing Starting Money ===\n";
    randMoney(players);

    int stockPrice = 500;
    int rounds = 5;

    int graph[WIDTH], history[HISTORY_SIZE];
    loadHistory(history, graph);

    for (int round = 1; round <= rounds; ++round) {
        cout << "\n=== Round " << round << " ===\n";
        cout << "Market News: " << generateMarketNews() << "\n";

        generateGraph(graph);
        displayGraph(graph);

        displayStatus(players, stockPrice);

        for (auto& player : players) {
            playerTurn(player, stockPrice);
            displayStatus(players, stockPrice);
        }

        int stockChange = calculateStockChange(graph);
        stockPrice += (stockPrice * stockChange) / 100;
        if (stockPrice < 1) stockPrice = 1;

        for (auto& player : players) {
            int totalValue = player.shares * stockPrice;
            player.profit_loss = totalValue + player.cash - 50000;
        }
    }

    saveHistory(graph);

    cout << "\n=== Game Over! ===\n";
    displayStatus(players, stockPrice);

    cout << "\n=== Player Titles ===\n";
    for (const auto& player : players) {
        cout << player.name << " is \"" << getTitle(player) << "\"\n";
    }
    return 0;
}
