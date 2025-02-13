#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));  
    
    const int WIDTH = 50;   
    const int HEIGHT = 20;  
    
    
    int graph[WIDTH];
    graph[0] = HEIGHT / 2;  
    
   
    for(int i = 1; i < WIDTH; i++) {
        
        int change = (rand() % 3) - 1;
        graph[i] = graph[i-1] + change;
        
       
        if(graph[i] < 0) graph[i] = 0;
        if(graph[i] >= HEIGHT) graph[i] = HEIGHT - 1;
    }
    
   
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(graph[w] == h) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}