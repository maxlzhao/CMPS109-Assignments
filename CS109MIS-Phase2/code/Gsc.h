//Gsc.h
#ifndef GSC_H
#define GSC_H
#include "Ssc.h"
using namespace std;

class Gsc: public Ssc //child class of Ssc Instruction
{
protected:
    string line; //first parameter
    int index; //second parameter
    string character; //third parameter
public:
    Gsc();//constructor
    Gsc(string str, int i, string c);
    virtual Instruction* clone(stringstream& ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "GSC";}
    virtual ~Gsc();//deconstructor
};

#endif