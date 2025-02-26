#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "graph.h"


using namespace std;

void loadHistory(int history[], int graph[]) {
    ifstream inFile("graph_history.txt");
    if (inFile) {
        for (int i = 0; i < HISTORY_SIZE; i++) {
            inFile >> history[i];
            graph[i] = history[i];
        }
        inFile.close();
    } else {
        for (int i = 0; i < HISTORY_SIZE; i++) {
            graph[i] = HEIGHT / 2;
        }
    }
}

void saveHistory(int graph[]) {
    ofstream outFile("graph_history.txt");
    for (int i = WIDTH - HISTORY_SIZE; i < WIDTH; i++) {
        outFile << graph[i] << " ";
    }
    outFile.close();
}

void generateGraph(int graph[]) {
    for (int i = HISTORY_SIZE; i < WIDTH; i++) {
        int change = (rand() % 3) - 1;
        graph[i] = graph[i - 1] + change;
        graph[i] = max(0, min(graph[i], HEIGHT - 1));
    }
}

void displayGraph(int graph[]) {
    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            cout << (graph[w] == h ? "|" : " ");
        }
        cout << endl;
    }
}

int calculateStockChange(int graph[]) {
    int last = graph[WIDTH - 1];
    int prev = graph[WIDTH - 2];

    if (last > prev) return 5;    // ขาขึ้น +5%
    if (last < prev) return -5;   // ขาลง -5%
    return 0;                     // ทรงตัว
}
