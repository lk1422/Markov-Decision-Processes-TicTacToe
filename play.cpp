#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <utility>
#include "env.h"
#include "Agent.h"
#include "play.h"


Play::Play(){
    a = Agent(.001,1);
    board = {B,B,B
            ,B,B,B
            ,B,B,B};
}

void Play::play(){
    std::cout << "Select your mark, X goes first" << std::endl;
    std::cout << "X or O" << std::endl;
    std::string answer;
    std::getline(std::cin, answer);

    answer.erase(std::remove_if(answer.begin(), answer.end(), ::isspace),answer.end());//Remove white space
    if (answer.size() != 1) {
        std::cout << "Invalid Input" << std::endl;
        return;
    }
    char move = tolower(answer[0]);
    if (move == 'x'){
        playerMark = X;
        computerMark=O;
    }else{
        playerMark = O;
        computerMark=X;
    }
    std::pair<std::vector<int>,int> state;

    printBoard(board);
    printNumberBoard();
    //if (playerMark == X) {
     //   processMove();
    //}


    
    while(a.getActions(state).size()) {
        printBoard(board);
        //Get computer move
        state = make_pair(board,computerMark);
        auto options = a.getActions(state);
        auto Policy = a.getPolicy(state);
        int index = std::find(Policy.begin(), Policy.end(), 1.0) - Policy.begin();
        board = a.enviorment.getState(options[index].first).first;
        printBoard(board);
        if(a.enviorment.isTerminal(a.enviorment.getID(std::make_pair(board,playerMark)))) {
            std::cout << "Computer Wins!!" <<std::endl;
            break;
        }
        processMove();
        if(a.enviorment.isTerminal(a.enviorment.getID(std::make_pair(board,computerMark)))) {
            std::cout << "YOU Win!!" <<std::endl;
            break;
        }
    }
}



void Play::processMove() {
    bool completed=false;
    std::cout << "Enter Your Square Number 1 - 9: " << std::endl;
    while(!completed){
        std::string answer;
        std::getline(std::cin, answer);

        answer.erase(std::remove_if(answer.begin(), answer.end(), ::isspace),answer.end());//Remove white space
        std::cout << answer << std::endl;
        std::cout << answer.size() << std::endl;
        if (answer.size() != 1) {
            std::cout << "Invalid Input" << std::endl;
            continue;
            }
        int square = stoi(answer);
        if (board[square-1] != B) {
            std::cout << "Invalid Input" << std::endl;
            continue;
            }
        board[square-1] = playerMark;
        completed = true;
    }
}
char Play::mark2char(int mark){
    if (mark==X) {
        return 'X';
    }
    else if(mark==O) {
        return 'O';
    }
    return ' ';
}
void Play::printBoard(std::vector<int> board ){
    for(int i=0; i<board.size(); i++){

        if(i%3==0) {
            std::cout << std::endl;
            std:: cout << "|";
            }
        std::cout << mark2char(board[i]) << " | ";
    }
    std::cout << std::endl;
}
void Play::printNumberBoard(){
    for(int i=0; i<9; i++){

        if(i%3==0) {
            std::cout << std::endl;
            std:: cout << "|";
            }
        std::cout << i+1 << " | ";
    }
    std::cout << std::endl;
}


