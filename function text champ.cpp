#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

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
