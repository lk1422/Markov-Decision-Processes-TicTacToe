#include <cassert>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "env.h"

Env::Env() {
    generateStates();
    TransitionStates = std::vector<std::vector<std::pair<int,int>>>(STATES.size());
    fillTransitionStates();
}

bool Env::TerminalState(std::vector<int> board) {
    //Checks to see if board is in the terminal state (Someone has won)
    for(int i=0; i<3; i++) {
        if(board[i*3] != B && board[(i*3)] == board[(i*3)+1] && board[(i*3)+1] ==  board[(i*3)+2] ) {// Check all horizontal cases
            return true;
        }
        else if (board[i]!=B && board[(i)] == board[(i+3)] && board[(i+3)] ==  board[(i+6)]) {//Checks all vertical cases
            return true;
        }
    }
    if (board[0] != B && board[0] == board[4] && board[4] == board[8]) {
        return true;
    }
    else if (board[2] != B && board[2] == board[4] && board[4] == board[6]) {
        return true;
    }
    return false;
}

void Env::generateStates(){//Using DP to find all state configurations
    std::vector<int> startState = {B, B, B, B, B, B, B, B, B};
    
    reward_map[0] = 0;
    State2ID[std::make_pair(startState,X)] = 0;
    State2ID[std::make_pair(startState,O)] = 1;
    STATES.push_back(std::make_pair(startState,X));
    STATES.push_back(std::make_pair(startState,O));
    for (int i=0; i<9; i++) {
      int stop_index=STATES.size();//This is the divider between the previous computations and the new ones  
      for(int j=0; j<stop_index; j++) {
          auto permutation = std::make_pair(STATES[j].first, STATES[j].second);
          permutation.first[i] = B;
          if (State2ID.find(permutation) == State2ID.end()) {//Not Found
              permutation.second=X;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
              permutation.second=O;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
          }
          permutation.first[i] = X;
          if (State2ID.find(permutation) == State2ID.end()) {//Not Found
              permutation.second=X;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
              if (TerminalState(permutation.first)){
                  reward_map[STATES.size()-1] = 1; 
                  TERMINAL_STATES[STATES.size()-1] = X;
              }
              permutation.second=O;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
              if (TerminalState(permutation.first)){
                  reward_map[STATES.size()-1] = 1; 
                  TERMINAL_STATES[STATES.size()-1] = X;
              }
          }
          permutation.first[i] = O;
          if (State2ID.find(permutation) == State2ID.end()) {//Not Found
              permutation.second=X;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
              if (TerminalState(permutation.first)){
                  reward_map[STATES.size()-1] = 1; 
                  TERMINAL_STATES[STATES.size()-1] = O;
              }
              permutation.second=O;
              STATES.push_back(permutation);
              reward_map[STATES.size()-1] = 0; 
              State2ID[permutation] = STATES.size()-1;
              if (TerminalState(permutation.first)){
                  reward_map[STATES.size()-1] = 1; 
                  TERMINAL_STATES[STATES.size()-1] = O;
              }
          }
        
      }
    }
}

void Env::fillTransitionStates(){ //Fills transition states based of the first mover X or O
    for(unsigned int i=0; i<STATES.size(); i++) {

        std::pair<std::vector<int>,int> board= STATES[i];
        for(int j=0; j<9;j++) {
            if(board.first[j] == B && TERMINAL_STATES.find(i) == TERMINAL_STATES.end()) {//Only consider non filled spots of non terminal boards
                    board.first[j] = board.second;
                    int move = board.second==X ? O : X;//After the next mvoe the turn swiches

                    int id = State2ID.find(make_pair(board.first,move))->second;
                    assert(State2ID.find(board) != State2ID.end());
                
                    int reward =0;
                    if (TERMINAL_STATES.find(id) != TERMINAL_STATES.end()) {
                        reward=1;
                    }
                    TransitionStates[i].push_back(std::make_pair(id,reward));
                    board.first[j] = B;
            }
        }
    }
}



void printVectorPair(std::vector<std::pair<int,int>> items) {
    for(auto& c: items){
    std::cout << c.first << ": " << c.second << ", ";
    
    }
    std::cout<<std::endl;
}






    
