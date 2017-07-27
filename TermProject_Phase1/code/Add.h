//file: Add.h
#ifndef ADD_H
#define ADD_H
#include "common.h"
#include "Sub.h"

class Add: public Instruction
{
  protected:
    string param1;                          // storage parameter
    vector<string> paramVec;                // vector to hold rest of parameters
    string varParam;
  public:
    Add(){} // constructor
    virtual Instruction * clone(stringstream &ss);
    void initialize(stringstream &ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "ADD";}
    virtual ~Add(){} // destructor
};

#endif
