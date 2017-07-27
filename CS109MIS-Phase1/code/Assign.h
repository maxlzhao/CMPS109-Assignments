//Assign.h
#include "Sub.h"

class Assign: public Instruction
{
protected:
    string param1; // variable to change
    string param2; // value to change to
public:
    Assign(){}; // default constructor
    virtual Instruction* clone(stringstream& ss);
    void initialize(stringstream& ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "ASSIGN";}
    virtual ~Assign(){} // destructor
    
};