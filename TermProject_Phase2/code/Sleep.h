//Sleep.h
#include "Sub.h"

class Sleep: public Instruction
{
protected:
    string param1; // duration to pause execution for
    string varParam;
public:
    Sleep(){};     // constructor
    virtual Instruction* clone(stringstream& ss);
    void initialize(stringstream& ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "SLEEP";}
    virtual ~Sleep(){} // destructor

};