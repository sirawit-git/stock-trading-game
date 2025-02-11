#include <iostream>
#include <vector>
using namespace std;

struct Player{
    string name; // ชื่อผู้เล่น
    double balance; // ยอดเงินคงเหลือ
    double startingMoney; // เงินเริ่มต้น(50,000)
    vector<double> trades; // ประวัติการเทรด
    int profitableTrades; // จำนวนครั้งที่เทรดแล้วได้กำไร
};

string getTitle(const Player& player){
    int highRiskTrades = 0, lowRiskTrades = 0, sameStockTrades = 0;
    int lossTrades = 0, totalTrades = player.trades.size();
    double maxLoss = 0, totalProfit = player.balance - player.startingMoney;
    double cashRatio = player.balance / player.startingMoney;

    for(double trade : player.trades) {
        if (trade >= 6000) highRiskTrades++;
        if (trade < 3000) lowRiskTrades++;
        if (trade < 0) {
            lossTrades++;
            if (-trade > maxLoss) maxLoss = -trade;
        }
    }

    if (player.balance > 150000) return "เศรษฐีใหม่";
    if (totalProfit >= player.startingMoney) return "พ่อค้าเลือดเย็น";
    if (highRiskTrades > totalTrades / 2) return "นักเสี่ยงดวง";
    if (lowRiskTrades == totalTrades) return "ปลอดภัยไว้ก่อน";
    if (cashRatio >= 0.7) return "สายเก็บออม";
    if (lossTrades > 0 && player.balance > player.startingMoney) return "นักลงทุนสายถึก";
    if (player.balance < 5000) return "จากดาดฟ้าสู่ดิน";
    if (maxLoss >= player.startingMoney * 0.5) return "หมดตัวเพราะไม้เดียว";
    if (lossTrades > totalTrades / 2) return "เจ้าพ่อดวงเกลือ";

    return "นักเทรดทั่วไป";
}

int main() {
    Player p1 = {"Alice", 160000, 50000, {8000, 7000, 10000, 5000, -120000}, 3};
    Player p2 = {"Prayun", 4000, 20000, {1000, 1000, -2000, -15000}, 1};

    cout << p1.name << " ได้ฉายา " << getTitle(p1) << endl;
    cout << p2.name << " ได้ฉายา " << getTitle(p2) << endl;

    return 0;
}