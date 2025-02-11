//ไม่ลงทุน
#include <iostream>
#include <conio.h> 
using namespace std;

int main() {
    cout << "ไม่ลงทุน\n";
    while (!_kbhit()); 

    char key = _getch(); 
    if (key == 13 || key == 32){
        cout << "คุณไม่ลงทุนในรอบนี้\n";
    } 

    return 0;
}
