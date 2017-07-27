//Div.h
#ifndef DIV_H
#define DIV_H
#include "Sub.h"

using namespace std;

class Div:public Sub
{
protected:
  string param1; // parameter to store result into
  string param2;
  string param3;
  string varParam2;
  string varParam3;
public:
	Div(); // constructor
	Div(string para1,string para2, string para3);
	virtual Instruction* clone(stringstream& ss);
  	virtual void process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec);
  	virtual string getName();
  	virtual string getType(){return "DIV";}
	virtual ~Div(); // destructor
};

#endif