//Jmp.h

#include "Sub.h"

class Jmp: public Instruction
{
protected:
    string labelName;
    string type;
public:
    Jmp();
    Jmp(string param1);
    virtual Instruction * clone(stringstream &ss);  //return new object
    void initialize(stringstream&ss);   //set internal variables
    virtual void process(unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec);    //placeholder to satisfy pure virtual method in instruction
    virtual string getName();
    virtual string getType();
    virtual ~Jmp();
};