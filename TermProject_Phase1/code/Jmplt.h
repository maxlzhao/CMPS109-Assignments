//Jmplt.h
#ifndef JMPLT_H
#define JMPLT_H
#include "Jmpgt.h"

class Jmplt:public Jmpgt
{
protected:
    string labelName;
    string param2;
    string param3;
    string varParam2;
    string varParam3;
public:
    Jmplt();
    Jmplt(string l, string p2, string p3);
    virtual Instruction *clone(stringstream& ss);   //return new object
    virtual void process(unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec);//update variable value from map
    virtual string getName();
    virtual string getType();
    virtual string getParam2();
    virtual string getParam3();
    virtual ~Jmplt();
};

#endif