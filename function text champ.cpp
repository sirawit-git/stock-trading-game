#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

vector<string> readFile(const string& filename) {
    vector<string> lines;
    ifstream file("news.txt");
    string line;

    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return lines;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

int getRandomLineNumber() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 150);
    return dist(gen);
}

int getRandomValue(int lineNumber) {
    static random_device rd;
    static mt19937 gen(rd());

    if (lineNumber >= 1 && lineNumber <= 50) {
        uniform_int_distribution<int> dist(850, 1300);
        return dist(gen);
    } 
    else if (lineNumber >= 51 && lineNumber <= 61) {
        uniform_int_distribution<int> dist(650, 850);
        return dist(gen);
    } 
    else if (lineNumber >= 62 && lineNumber <= 70) {
        uniform_int_distribution<int> dist(400, 600);
        return dist(gen);
    }
    else if (lineNumber >= 71 && lineNumber <= 76) {
        uniform_int_distribution<int> dist(300, 400);
        return dist(gen);
    } 
    else if (lineNumber >= 77 && lineNumber <= 126) {
        uniform_int_distribution<int> dist(200, 300);
        return dist(gen);
    }
    else {
        uniform_int_distribution<int> dist(100, 200);
        return dist(gen);
    }
}

int main() {
    vector<string> lines = readFile("news.txt"); // ใช้ชื่อไฟล์ที่ถูกต้อง

    if (lines.empty()) {
        cerr << "File is empty or not found!" << endl;
        return 1;
    }

    int randomLine = getRandomLineNumber();
    int randomValue = getRandomValue(randomLine);

    cout << "Random line number: " << randomLine << endl;
    cout << "Random value: " << randomValue << endl;
    cout << "News: " << lines[randomLine - 1] << endl; // แสดงข่าวจากบรรทัดที่สุ่มได้

    return 0;
}