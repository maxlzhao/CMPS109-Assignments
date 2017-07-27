#include "common.h"
#include "Sub.h"
#include "DataType.cpp"
// #include "Instruction.h"
using namespace std;


class Var: public Instruction
{
	protected:
		//hold a DataType object
		DataType* d;
		string stringN;
		string stringT;
		string defaultVal;
		string size;
	public:
		Var();
		Var(string s_stringN, string s_stringT, string defaultVal, string size);
		virtual Instruction * clone(stringstream &ss);
    	void initialize(stringstream &ss);
		virtual void process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec);
		virtual string getName();
		virtual string getType(){return "VAR";}
		virtual ~Var();
};
