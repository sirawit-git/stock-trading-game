#include <iostream>
#include <fstream>
#include <vector>
#include <random>


std::vector<std::string> readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return lines;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();
    return lines;
}


int getRandomLineNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 150);
    return dist(gen);
}

int getRandomValue(int lineNumber) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if (lineNumber >= 1 && lineNumber <= 50) {
        std::uniform_int_distribution<int> dist(750, 1000);
        return dist(gen);
    } 
    else if (lineNumber >= 51 && lineNumber <= 100) {
        std::uniform_int_distribution<int> dist(400, 650);
        return dist(gen);
    } 
    else if (lineNumber >= 101 && lineNumber <= 150) {
        std::uniform_int_distribution<int> dist(250, 350);
        return dist(gen);
    }

    return -1; 
}

int main() {
   
    std::vector<std::string> lines = readFile("new.txt");

    if (lines.empty()) {
        std::cerr << "File is empty or not found!" << std::endl;
        return 1;
    }

    int randomLine = getRandomLineNumber();
    int randomValue = getRandomValue(randomLine);
    
    std::cout << "Random Line Number: " << randomLine << std::endl;
    std::cout << "Random Value: " << randomValue << std::endl;

    if (randomLine > 0 && randomLine <= lines.size()) {
        std::cout << "Line Content: " << lines[randomLine - 1] << std::endl;
    } else {
        std::cerr << "Random line number is out of range!" << std::endl;
    }

    return 0;
}