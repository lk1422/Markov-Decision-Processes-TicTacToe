#include <vector>
#include <utility>
#include "env.h"

#ifndef Agent_H
#define Agent_H
class Agent{
    /*Agent will interact with the envioirment(tiktaktoe board)
     *
     * The Actions from a given state is found by founding the corresponding transitional IDs from that state
     * So each action is determinisitic as the action is the choice of what the next state should be
     * There fore the "shape" of our policy vector should be the same as the transitional states
     * The State value should have the same size as the state size as it is giving a value to each state
     */

    public:
    Agent(double theta, double gamma);
    Agent();

    std::vector<std::pair<int,int>> getActions(std::pair<std::vector<int>, int> s) {return enviorment.getOptionsBoard(s.first, s.second);}
    std::vector<std::pair<int,int>> getActions(int id) {return enviorment.getOptionsID(id);}
    std::vector<double>             getPolicy (std::pair<std::vector<int>,int> board) {return Policy[(enviorment.getID(board))];}
    double                          getStateValue(std::pair<std::vector<int>,int> board) {return StateValue[(enviorment.getID(board))];}
    Env enviorment;//Holds the state information 




    private:
    double theta; //Variable which controls precision of policyevaluation
    double gamma; //DecayRate for expected return since this task is episodic gamma=1

    std::vector<std::vector<double>> Policy;//Same dimensions of transSTATES but instead it holds the probablity from the policy
    std::vector<double> StateValue;

    void initStateInfo(); 
    
    void PolicyEvaluation();//Computes the StateValue pairs for each state given current policy
    void PolicyIteration();

    /* Helpers */
    int argMax(int ID);
    int argMin(int ID);
    int argMax(std::vector<double> probs);
    void setZeros(int index);
    
};

#endif
