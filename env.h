#include <vector>
#include <utility>
#include <unordered_map>
#include <iostream>
#include "Hashing.h"

#ifndef Env_H
#define Env_H
#define X 0
#define O 1
#define B 2



class Env{
    //Enviorment for teh tik tak toe board 
    public:
    int              getStateSize() {return STATES.size();}
    std::vector<int> getBoard(int id) {return STATES[id].first;}
    int              getMove(int ID) {return STATES[ID].second;}//Returns the which players move it is in a given state
    int              getID(std::pair<std::vector<int>,int> s) {return State2ID.find(s)->second;}
    std::pair<std::vector<int> , int> getState(int ID) {return STATES[ID];}//Returns the internals from the state vector

    std::vector<std::pair<int,int>> getOptionsBoard(std::vector<int> board, int move) {return TransitionStates[(State2ID.find(std::make_pair(board,move))->second)];}
    std::vector<std::pair<int,int>> getOptionsID(int ID) {return TransitionStates[ID];}

    bool isTerminal(int ID) {return (TERMINAL_STATES.find(ID)!=TERMINAL_STATES.end());} //Checks if board is in precomputed terminal states




    Env();
    
    private:
    std::unordered_map<int, int> reward_map; //Maps the state ID to the reward

    std::unordered_map<std::pair<std::vector<int>, int>, int, hash_pair> State2ID;//Maps each state to its ID(index for the STATES VECTOR
    std::vector<std::vector<std::pair<int,int>>> TransitionStates;//Maps a state to its possible transition states and its reward
    std::vector<std::pair<std::vector<int>,int>> STATES;//State containing the baord geometry and move
    std::unordered_map<int,int> TERMINAL_STATES;//Maps the state id to the winner


    bool TerminalState(std::vector<int> board);// Manually Checks if board is terminal (doesnt consider ties)
    void generateStates();//Generates all possible states and fills all the information arrays 
    void fillTransitionStates();//Generates possible next states from all states


};

/* HELPERS */
void printVectorPair(std::vector<std::pair<int,int>> items);

template<typename T>
void printVector(std::vector<T> items){
    for(auto& c: items){
    std::cout << c << ", ";
    }
    std::cout<<std::endl;
}

#endif
    




