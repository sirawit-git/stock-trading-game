#include <iostream>
#include <vector>
#include <string>

using namespace std;

// โครงสร้างข้อมูลของผู้เล่น  ทิม
struct Player {
    string name;
    double money;
};

// ฟังก์ชันสำหรับสร้างผู้เล่นและกำหนดเงินเริ่มต้นให้กับผู้เล่นแต่ละคน ของทิม
vector<Player> initializePlayers(int numPlayers) {
    vector<Player> players;          // สร้าง vector เปล่าสำหรับเก็บข้อมูลผู้เล่น
    double startMoney = 50000.0;       // จำนวนเงินเริ่มต้น

    for (int i = 0; i < numPlayers; i++) {
        Player p;                    // สร้างตัวแปร Player แบบชั่วคราว
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> p.name;               // รับชื่อผู้เล่น
        p.money = startMoney;        // กำหนดเงินเริ่มต้นให้กับผู้เล่น
        players.push_back(p);        // เพิ่มผู้เล่นเข้าไปใน vector
    }

    return players;
}

// ฟังก์ชันสำหรับแสดงยอดเงินของผู้เล่น  เริ่มจากนี่
void displayPlayers(const vector<Player> &players) {
    cout << "\n--- Player Balances ---\n";
    for (int i = 0; i < players.size(); i++) {
        cout << "Name: " << players[i].name 
             << " --> Balance: " << players[i].money << " Baht."<< endl;
    }
}


int main() {
    int numPlayers;

    cout << "Enter number of players: "; //ทิม
    cin >> numPlayers;   // รับจำนวนผู้เล่นจากผู้ใช้  ทิม

    // สร้างผู้เล่นและแสดงยอดเงินของผู้เล่น
    vector<Player> players = initializePlayers(numPlayers);
    displayPlayers(players);

    return 0;
}
