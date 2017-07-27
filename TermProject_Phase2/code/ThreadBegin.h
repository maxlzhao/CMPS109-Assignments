//file: ThreadBegin.h
#ifndef THREADBEGIN_H
#define THREADBEGIN_H
#include "common.h"
#include "Sub.h"

class ThreadBegin: public Instruction
{
  protected:
    vector<string> paramVec;                // vector to hold rest of parameters
  public:
    ThreadBegin(){} // constructor
    virtual Instruction * clone(stringstream &ss);
    void initialize(stringstream &ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "ThreadBegin";}
    virtual ~ThreadBegin(){} // destructor
};

#endif
