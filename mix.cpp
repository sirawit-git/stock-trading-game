//ภาพรวม

void displayStatusWithGraph(const vector<Player>& players, int stockPrice, int graph[]) {
    cout << "\n--- Market Graph & Player Status ---\n";

    // เรียกใช้ฟังก์ชันวาดกราฟที่แก้ไขแล้ว
    displayGraph(graph);

    // แสดงสถานะหุ้น
    cout << "   Stock Price: " << stockPrice << " Baht" << endl;
    cout << "   Player        Cash      Shares  Profit/Loss" << endl;

    for (const auto& player : players) {
        cout << "   " << setw(10) << left << player.name
             << setw(10) << player.cash
             << setw(8)  << player.shares
             << setw(8)  << player.profit_loss << endl;
    }

    cout << "------------------------------------------------------------\n";
}
