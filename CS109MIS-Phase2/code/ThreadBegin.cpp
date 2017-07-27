// ThreadBegin.cpp

#include "ThreadBegin.h"
#include "ThreadRunner.h"

using namespace std;
  
// creating a new threadbegin object based on the provided string stream    
Instruction* ThreadBegin::clone(stringstream& ss){
    ThreadBegin* threadbegin = new ThreadBegin();
    threadbegin->initialize(ss);
    return threadbegin;
}

// parses and initializes variables in threadbegin 
void ThreadBegin::initialize (stringstream& ss){

}

// processing of threadbegin functionality
void ThreadBegin::process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec){


}

string ThreadBegin::getName()
{
    return "";
}

