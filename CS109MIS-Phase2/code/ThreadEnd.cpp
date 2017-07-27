// ThreadEnd.cpp

#include "ThreadEnd.h"
#include "ThreadRunner.h"

using namespace std;
  
// creating a new Add object based on the provided string stream    
Instruction* ThreadEnd::clone(stringstream& ss){
    ThreadEnd* threadend = new ThreadEnd();
    threadend->initialize(ss);
    return threadend;
}

// parses and initializes variables in Add 
void ThreadEnd::initialize (stringstream& ss){

}

// processing of addition functionality
void ThreadEnd::process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec){


}

string ThreadEnd::getName()
{
    return "";
}

