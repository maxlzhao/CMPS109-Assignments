//file: ThreadEnd.h
#ifndef THREADEND_H
#define THREADEND_H
#include "common.h"
#include "Sub.h"

class ThreadEnd: public Instruction
{
  protected:
    vector<string> paramVec;                // vector to hold rest of parameters
  public:
    ThreadEnd(){} // constructor
    virtual Instruction * clone(stringstream &ss);
    void initialize(stringstream &ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "ThreadEnd";}
    virtual ~ThreadEnd(){} // destructor
};

#endif
