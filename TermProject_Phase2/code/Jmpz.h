//Jmpz.h
#ifndef JMPZ_H
#define JMPZ_H
#include "Sub.h"

class Jmpz:public Instruction
{
protected:
    string labelName;
    string param2;
    string varParam2;
public:
    Jmpz();
    Jmpz(string l, string c);
    virtual Instruction * clone(stringstream &ss);  //return new object
    void initialize(stringstream &ss);  
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);//update variable value from map
    virtual string getName();
    virtual string getType();
    virtual string getParam2();
    virtual ~Jmpz();
    
};

#endif