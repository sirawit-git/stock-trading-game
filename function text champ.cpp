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
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 150);
    return dist(gen);
}

int getRandomValue(int lineNumber) {
    random_device rd;
    mt19937 gen(rd());

    if (lineNumber >= 1 && lineNumber <= 50) {
        uniform_int_distribution<int> dist(750, 1000);
        return dist(gen);
    } 
    else if (lineNumber >= 51 && lineNumber <= 100) {
        uniform_int_distribution<int> dist(400, 650);
        return dist(gen);
    } 
    else if (lineNumber >= 101 && lineNumber <= 150) {
        uniform_int_distribution<int> dist(250, 350);
        return dist(gen);
    }

    return -1; 
}

int main() {
    vector<string> lines = readFile("new.txt");

    if (lines.empty()) {
        cerr << "File is empty or not found!" << endl;
        return 1;
    }

    int randomLine = getRandomLineNumber();
    int randomValue = getRandomValue(randomLine);
    
    cout << "Random Line Number: " << randomLine << endl;
    cout << "Random Value: " << randomValue << endl;

    if (randomLine > 0 && randomLine <= lines.size()) {
        cout << "Line Content: " << lines[randomLine - 1] << endl;
    } else {
        cerr << "Random line number is out of range!" << endl;
    }

    return 0;
}