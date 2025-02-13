#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void randMoney(int players, int &Currentlymoney) {
    vector<int> money(players, 0);
    int amounts[] = {1000, 2000, -1000, -2000, 5000, 3000, 4000, -2000,4600,-3000,5600,4000,-3440,1000};
    int numAmounts = sizeof(amounts) / sizeof(amounts[0]);

    srand(time(0));

    for (int i = 0; i < players; i++) {
        money[i] = amounts[rand() % numAmounts];
        Currentlymoney += money[i]; 
        cout << "Player " << i + 1 << " gets: " << money[i] << " baht"
             << " | Remaining money: " << Currentlymoney << " baht\n";
    }
}

int main() {
    int players = 3;
    int Currentlymoney = 50000; 

    randMoney(players, Currentlymoney);

    return 0;
}