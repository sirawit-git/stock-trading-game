#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

pair<string, int> generateMarketNews() {
    vector<string> news;
    ifstream file("news.txt");
    string line;

    if (!file) {
        cerr << "Error: Cannot open news.txt!\n";
        return make_pair("No news available.", -1);
    }

    while (getline(file, line)) {
        if (!line.empty()) news.push_back(line);
    }
    
    file.close();

    if (news.empty()) return make_pair("No news available.", -1);

    // สุ่ม
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, news.size() - 1);
    
    int randomIndex = dist(gen); // ตำแหน่งของข่าวที่สุ่มได้
    return make_pair(news[randomIndex], randomIndex + 1); // +1 เพราะ index เริ่มจาก 0 แต่บรรทัดเริ่มที่ 1
}
