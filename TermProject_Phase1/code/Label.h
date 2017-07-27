//Label.h
#ifndef LABEL_H
#define LABEL_H 
#include "Sub.h"

class Label:public Instruction
{
protected:
    string name;
public:
    Label();
    Label(string param1);
    virtual Instruction * clone(stringstream &ss);  //return new object
    void initialize(stringstream &ss);  //initialize protected vars
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec); //put into varMap name of label and line#
    virtual string getName();
    virtual string getType(){return "LABEL";}
    virtual ~Label();
};

#endif