#include <vector>
#include <cmath>
#include <iostream>
#include <utility>
#include <algorithm>
#include "Agent.h"
#include "env.h"


Agent::Agent(double theta, double gamma) {
    this->theta=theta;
    this->gamma=gamma;
    StateValue = std::vector<double>(enviorment.getStateSize(), 0);
    Policy =     std::vector<std::vector<double>>(enviorment.getStateSize());
    initStateInfo();
    PolicyIteration();
}
Agent::Agent() {

}

void Agent::initStateInfo() {
    for(int i=0; i<enviorment.getStateSize(); i++) {
        int numActions = getActions(i).size();

        if (numActions==0) {
            continue;
        }
        std::vector<double> temp(numActions, (double)1/numActions);
        
        Policy[i] = temp;
    }

}

void Agent::PolicyEvaluation(){
    double delta =1; 
    while(delta > theta) {
        delta =0;
        for(int i=0; i<enviorment.getStateSize(); i++) {
           if (enviorment.isTerminal(i) || Policy[i].size()==0) {//Dont Update Terminal States (Ties are not stored in Terminal State)
               continue;
           }
           double sum=0;
           for(unsigned int j=0; j<Policy[i].size(); j++){//Pair of ID, reward
               double policy_probability = Policy[i][j];
               auto s_prime = getActions(i)[j];//The state from preforming action (happens deterministically)
               double reward = (enviorment.getMove(i)==X ? s_prime.second : s_prime.second * -1);//Make Os reward negative
               sum += (policy_probability) * (reward + gamma*StateValue[s_prime.first]);
           }
           double old_value = StateValue[i];
           StateValue[i] = sum;
           
           delta = std::max(delta,std::fabs(old_value-sum));
        }
    }
}




void Agent::PolicyIteration(){
    bool policyStable = false;
    while(!policyStable) {
        PolicyEvaluation();

        for(unsigned int i=0; i<Policy.size(); i++) {
            if(Policy[i].size() < 2 ) {//Ignore Terminals and dterministic states (no update neccessary in either)
                continue;
            }
            int oldPolicy = argMax(Policy[i]);//Get index of previous action
            int newPolicy = (enviorment.getMove(i)==X ? argMax(i):argMin(i));//MinMax for 0-Summality

            setZeros(i);
            Policy[i][newPolicy]=1;
            
            
            
            if(oldPolicy==newPolicy ) {

                policyStable = true;
            }else{
                policyStable = false;
            }
        }
    }
}



void Agent::setZeros(int index){
    for(auto &val : Policy[index]) {
        val=0;
    }
}
int Agent::argMax(int ID) {
    int index=-1;
    double Value = -2;
    auto a = getActions(ID);
    int counter = 0; 
    for(std::pair<int,int> &Id_Reward : a) {
        //Get StateValue
        double s_prime = StateValue[Id_Reward.first] + Id_Reward.second;
        if (s_prime > Value) {
            Value = s_prime;
            index = counter;
        }
        counter++;
    }
    return index;
}
int Agent::argMin(int ID) {
    int index=-1;
    double Value = 2;
    auto a = getActions(ID);
    int counter = 0; 
    for(std::pair<int,int> &Id_Reward : a) {
        //Get StateValue
        double s_prime = StateValue[Id_Reward.first] + Id_Reward.second;
        if (s_prime < Value) {
            Value = s_prime;
            index = counter;
        }
        counter++;
    }
    return index;
}

int Agent::argMax(std::vector<double> probs) { 
    double maximum=-2;
    int index = -1;
    for(unsigned int i=0; i<probs.size(); i++) {
        if (probs[i] > maximum) {
            maximum = probs[i];
            index = i;
        }
    }
    return index;
}










 

