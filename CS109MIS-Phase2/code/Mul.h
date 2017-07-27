//file: Mul.h
#ifndef MUL_H
#define MUL_H
#include "common.h"
#include "Sub.h"

class Mul: public Instruction
{
  protected:
    string param1;            // parameter to store product in
    vector<string> paramVec;  // vector to store parameters to be multiplied
    string varParam;
  public:
    Mul(){} // constructor
    virtual Instruction * clone(stringstream &ss);
    void initialize(stringstream &ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "MUL";}
    virtual ~Mul(){} // destructor
};

#endif
