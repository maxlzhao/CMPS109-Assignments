//Jmpgt.h
#ifndef JMPGT_H
#define JMPGT_H
#include "Sub.h"

class Jmpgt:public Instruction
{
protected:
    string labelName;
    string param2;
    string varParam2;
    string varParam3;
    string param3;
public:
    Jmpgt();
    Jmpgt(string l, string p2, string p3);
    virtual Instruction* clone(stringstream& ss);   //return new object
    void initialize(stringstream& ss);  //initialize internal variables
    virtual void process(unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType();
    virtual string getParam2();
    virtual string getParam3();
    virtual ~Jmpgt();
};

#endif