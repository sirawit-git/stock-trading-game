// ฟังก์ชันขายหุ้น
#include <iostream>
using namespace std;

void sellTrade() {
    double amount;
    
    do {
        cout << "กรุณากรอกราคาหุ้นที่ต้องการขาย (ไม่น้อยกว่า 5000 บาท): ";
        cin >> amount;
        
        if (amount < 5000) {
            cout << "จำนวนเงินที่กรอกน้อยเกินไป กรุณาลองใหม่!" << endl;
        }
    } while (amount < 5000);
    
    cout << "คุณได้ทำการขายหุ้นเป็นจำนวน " << amount << " บาท" << endl;
}

int main() {
    sellTrade(); // เรียกใช้ฟังก์ชันขายสินค้า
    return 0;
}
