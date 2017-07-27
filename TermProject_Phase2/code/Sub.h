//file: Sub.h
#ifndef SUB_H
#define SUB_H
#include "common.h"
#include "Instruction.h"

class Sub: public Instruction
{
  protected:
    string param1; // difference storage variable
    string param2; // first parameter
    string param3; // second parameter 
    string varParam2;
    string varParam3;
  public:
    Sub(); // constructor
    Sub(string para1, string para2, string para3);
    virtual Instruction * clone(stringstream &ss);
    void initialize(stringstream &ss);
    virtual void process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "SUB";}
    virtual ~Sub(); // destructor
};

#endif
