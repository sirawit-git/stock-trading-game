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


using namespace std;

void displayStatus(const vector<Player>& players, int stockPrice) {
    SetConsoleColor(5);
    cout << "\n--- Current Status ---\n";
    cout << "Stock Price: " << stockPrice << " Baht\n";
    
    vector<string> names;
    vector<int> cash, shares, profit_loss;

    for (const auto& player : players){
        names.push_back(player.name);
        cash.push_back(player.cash);
        shares.push_back(player.shares);
        profit_loss.push_back(player.profit_loss);
    }

    DrawPlayerStatusBoxes(names, cash, shares, profit_loss);
    SetConsoleColor(7);


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
        SetConsoleColor(2); cout << "[1] Buy Shares\n";
        SetConsoleColor(4); cout << "[2] Sell Shares\n";
        SetConsoleColor(13); cout << "[3] Skip Turn\n";
        SetConsoleColor(7); cout << "Choice: ";
        SetConsoleColor(6);

        if (!(cin >> choice)) {
            SetConsoleColor(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            SetConsoleColor(4);
            cout << "Invalid input! Please enter a number (1, 2, or 3).\n";
            SetConsoleColor(7);
            continue;
        }

        if (choice == 2 && player.shares == 0) {  
            SetConsoleColor(4);
            cout << "You have no shares to sell! Choose another option.\n";
            SetConsoleColor(7);
            continue; // ให้ผู้เล่นเลือกใหม่แทนที่จะออกจากฟังก์ชัน
        }

        if (choice >= 1 && choice <= 3) {
            break; 
        } else {
            SetConsoleColor(4);
            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
            SetConsoleColor(7);
        }
    }

    if (choice == 1) {  // Buy Shares
        while (true) {
            SetConsoleColor(7);
            cout << "How many shares would you like to buy? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            SetConsoleColor(2);
            cout << "You want to buy : ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                SetConsoleColor(4);
                cout << "Invalid input! Enter a valid number.\n";
                SetConsoleColor(7);
                continue;
            }

            if (amount == 0) {
                SetConsoleColor(2);
                cout << "Returning to main menu...\n";
                SetConsoleColor(7);
                return playerTurn(player, stockPrice);  // **กลับไปเลือกเมนูใหม่**
            }

            if (amount < 0) {
                cout << "Invalid amount! Enter a positive number.\n";
                continue;
            }

            int cost = amount * stockPrice;
            if (cost > player.cash) {
                SetConsoleColor(4);
                cout << "Not enough cash! You only have " << player.cash << " Baht.\n";
                SetConsoleColor(7);
            } else {
                player.cash -= cost;
                player.shares += amount;
                player.trades.push_back(-cost);
                break;
            }
            SetConsoleColor(7);
        }
    } 
    else if (choice == 2) {  // Sell Shares
        while (true) {
            SetConsoleColor(7);
            cout << "How many shares would you like to sell? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            SetConsoleColor(4);
            cout << "You want to sell : ";

            if (!(cin >> amount)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Enter a valid number.\n";
                continue;
                SetConsoleColor(7);
            }

            if (amount == 0) {
                SetConsoleColor(2);
                cout << "Returning to main menu...\n";
                SetConsoleColor(7);

                return playerTurn(player, stockPrice);  // **กลับไปเลือกเมนูใหม่**
            }

            if (amount < 0) {
                cout << "Invalid amount! Enter a positive number.\n";
                continue;
            }


            if (amount > player.shares) {
                SetConsoleColor(4);
                cout << "Not enough shares! You only have " << player.shares << " shares.\n";
                SetConsoleColor(7);
            } else {
                int revenue = amount * stockPrice;
                player.cash += revenue;
                player.shares -= amount;
                player.trades.push_back(revenue);
                break;
            }
            SetConsoleColor(7);
        }
    }
}


int main() {

    SetConsoleShow("My Console App");//ตั้งชื่อ console
    
    srand(time(0));

    int numPlayers;

    while (true){
        cout << "Number of players (3-5): ";
        if(cin >> numPlayers && numPlayers >= 3 && numPlayers <= 5){
            break;
        }else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number 3-5\n";
        }
    }

    vector<Player> players = initializePlayers(numPlayers);
    
    SetConsoleColor(9);//สีฟ้า
    cout << "\n=== Randomizing Starting Money ===\n";
    SetConsoleColor(7);

    randMoney(players);

    int stockPrice = 500;
    int rounds = 5;

    int graph[WIDTH], history[HISTORY_SIZE];
    loadHistory(history, graph);

    for (int round = 1; round <= rounds; ++round) {
        cout << "\n=== Round " << round << " ===\n";//รอบ
        cout << "Market News: " << generateMarketNews() << "\n"; //ข่าว

        generateGraph(graph);
        displayGraph(graph);

        displayStatus(players, stockPrice);

        for (auto& player : players) {
            playerTurn(player, stockPrice);
            displayStatus(players, stockPrice);
        }

        int stockChange = calculateStockChange(graph);
        stockPrice += (stockPrice * stockChange) / 20;
        if (stockPrice < 1) stockPrice = 1;

        for (auto& player : players) {
            int totalValue = player.shares * stockPrice;
            player.profit_loss = totalValue + player.cash - 50000;
        }
    }

    saveHistory(graph);
    cout << endl;
    cout << endl;
    SetConsoleColor(4);
    cout << "********************************\n";
    cout << "*                              *\n";
    cout << "*";
    SetConsoleColor(14);
    cout <<"          GAME OVER!          ";
    SetConsoleColor(4);
    cout << "*\n";
    cout << "*                              *\n";
    cout << "********************************\n";
    SetConsoleColor(7);
    cout << endl;

    //สรุปสถานะ
    displayStatus(players, stockPrice);

    displayVictory(players);//ผู้ชนะ

   
    rankPlayers(players); // แสดงลำดับผู้ชนะ

    ShowTitlePlayerder(players);//แสดงฉายา
    
    return 0;
}
