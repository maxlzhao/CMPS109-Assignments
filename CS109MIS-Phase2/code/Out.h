//Out.h
#include "Sub.h"
using namespace std;

class Out: public Instruction
{
protected:
    vector<string> paramVec;
public:
    Out(){};
    virtual Instruction* clone(stringstream& ss);
    void initialize(stringstream& ss);
    virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
    virtual string getName();
    virtual string getType(){return "OUT";}
    virtual ~Out(){}
    
};