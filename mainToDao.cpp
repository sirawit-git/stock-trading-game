#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include "player.h"
#include "graph.h"
#include "console.h" 
// ดาวเอามาใส่ที

using namespace std;

void displayTextArt() {
    cout << "\n\n";
    cout << "*****************************************\n";
    cout << "*                                       *\n";
    cout << "*    WELCOME TO THE STOCK MARKET GAME   *\n";
    cout << "*                                       *\n";
    cout << "*****************************************\n";
    cout << "\n\n";
}

void displayRoundArt(int round) {
    cout << "\n";
    cout << "***************************** ROUND " << round << " *****************************\n";
    cout << "*                                                                       *\n";
    cout << "*   Let's make some BIG moves in the STOCK MARKET this round!            *\n";
    cout << "*   The market is full of opportunities. Are you ready to take a risk?    *\n";
    cout << "*                                                                       *\n";
    cout << "*************************************************************************\n";
    cout << "\n";
}

void displayStatusWithGraph(const vector<Player>& players, int stockPrice , int graph[]) {
    cout << "\nStock Graph:\n";
    generateGraph(graph);
    displayGraph(graph);
    cout << endl;  // พิมพ์บรรทัดใหม่

    cout << setw(68) << " " <<  "\n--- Current Status ---\n";
    cout << setw(48) << " " << "Stock Price: " << stockPrice << " Baht\n";
    for (const auto& player : players) {
        cout << setw(48) << " " << player.name << " | Cash: " << player.cash 
             << " | Shares: " << player.shares
             << " | Profit/Loss: " << player.profit_loss << "\n";
    }
    cout << setw(48) << " " << "----------------------\n";
}

void displayStatus(const vector<Player>& players, int stockPrice) {
    cout << "\n--- Current Status ---\n";
    cout << "Stock Price: " << stockPrice << " Baht\n";
    for (const auto& player : players) {
        cout << player.name << " | Cash: " << player.cash << " | Shares: " << player.shares
             << " | Profit/Loss: " << player.profit_loss << "\n";
    }
    cout << "----------------------\n";
}

int calculateStockPrice(int newsLine) {
    if (newsLine >= 1 && newsLine <= 21) return rand() % (1300 - 850 + 1) + 850;
    if (newsLine >= 22 && newsLine <= 48) return rand() % (850 - 650 + 1) + 650;
    if (newsLine >= 49 && newsLine <= 85) return rand() % (600 - 400 + 1) + 400;
    if (newsLine >= 86 && newsLine <= 109) return rand() % (400 - 300 + 1) + 300;
    if (newsLine >= 110 && newsLine <= 131) return rand() % (300 - 200 + 1) + 200;
    return 0; // เผื่อกรณีไม่ตรงกับช่วงที่กำหนด
}


pair<int, string> generateMarketNews() {
    vector<pair<int, string>> newsList;
    ifstream file("news_2.txt");
    string line;
    int lineNumber = 0;
    
    if (!file) {
        cerr << "Error: Cannot open news_2.txt!\n";
        return {-1, "No news available."};
    }
    
    while (getline(file, line)) {
        lineNumber++;
        if (!line.empty()) {
            newsList.push_back({lineNumber, line});
        }
    }
    file.close();
    
    if (newsList.empty()) return {-1, "No news available."};
    
    int randomIndex = rand() % newsList.size();
    return newsList[randomIndex];
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

void displayEndGameArt() {
    cout << "\n\n";
    cout << "*********************************************************************\n";
    cout << "*                                                                   *\n";
    cout << "*  CONGRATULATIONS! YOU'VE REACHED THE END OF THE STOCK MARKET GAME! *\n";
    cout << "*  Thank you for playing. Now, let's see who the real investor is!   *\n";
    cout << "*                                                                   *\n";
    cout << "*********************************************************************\n";
    cout << "\n\n";
}

int main() {
    pair<int, string> result = generateMarketNews();
    srand(time(0));

    displayTextArt();

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
        displayRoundArt(round);
        cout << "\n=== Round " << round << " ===\n";
        
        // สุ่มข่าวและกำหนดราคาหุ้น
        pair<int, string> news = generateMarketNews();
        cout << "Market News: " << news.second << "\n"; 
        stockPrice = calculateStockPrice(news.first);

        displayStatusWithGraph(players, stockPrice, graph);

        for (auto& player : players) {
            playerTurn(player, stockPrice);
            displayStatus(players, stockPrice);
        }

        for (auto& player : players) {
            int totalValue = player.shares * stockPrice;
            player.profit_loss = totalValue + player.cash - 50000;
        }
    }

    saveHistory(graph);

    cout << "\n=== Game Over! ===\n";
    displayEndGameArt();
    displayStatus(players, stockPrice);

    cout << "\n=== Player Titles ===\n";
    for (const auto& player : players) {
        cout << player.name << " is \"" << getTitle(player) << "\"\n";
    }
    return 0;
}
