#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
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
    int choice = 0, amount = 0;

    // ตรวจสอบตัวเลือกให้ถูกต้อง
    while (true) {
        cout << "\n" << player.name << ", what would you like to do?\n";
        cout << "[1] Buy Shares\n[2] Sell Shares\n[3] Skip Turn\n";
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
            continue;
        }

        if (choice == 2 && player.shares == 0) {  
            cout << "You have no shares to sell! Choose another option.\n";
            continue; // ให้ผู้เล่นเลือกใหม่แทนที่จะออกจากฟังก์ชัน
        }

        if (choice >= 1 && choice <= 3) {
            break; 
        } else {
            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }

    if (choice == 1) {  // Buy Shares
        while (true) {
            cout << "How many shares would you like to buy? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            cout << "You want to buy : ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid number.\n";
                continue;
            }

            if (amount == 0) {
                cout << "Returning to main menu...\n";
                return playerTurn(player, stockPrice);  // **กลับไปเลือกเมนูใหม่**
            }

            if (amount < 0) {
                cout << "Invalid amount! Enter a positive number.\n";
                continue;
            }

            int cost = amount * stockPrice;
            if (cost > player.cash) {
                cout << "Not enough cash! You only have " << player.cash << " Baht.\n";
            } else {
                player.cash -= cost;
                player.shares += amount;
                player.trades.push_back(-cost);
                break;
            }
        }
    } 
    else if (choice == 2) {  // Sell Shares
        while (true) {
            cout << "How many shares would you like to sell? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            cout << "You want to sell : ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid number.\n";
                continue;
            }

            if (amount == 0) {
                cout << "Returning to main menu...\n";
                return playerTurn(player, stockPrice);  // **กลับไปเลือกเมนูใหม่**
            }

            if (amount < 0) {
                cout << "Invalid amount! Enter a positive number.\n";
                continue;
            }


            if (amount > player.shares) {
                cout << "Not enough shares! You only have " << player.shares << " shares.\n";
            } else {
                int revenue = amount * stockPrice;
                player.cash += revenue;
                player.shares -= amount;
                player.trades.push_back(revenue);
                break;
            }
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
