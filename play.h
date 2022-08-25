#include <iostream>
#include <vector>
#include <utility>
#include "env.h"
#include "Agent.h"

#ifndef Play_H
#define Play_H
class Play{

    public:
    Play();
    void play();

    private:
    std::vector<int> board;
    Agent a;
    char mark2char(int mark);
    void printBoard(std::vector<int> board);
    void printNumberBoard();
    void processMove();
    int playerMark;
    int computerMark;
};
    
#endif
