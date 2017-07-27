//Div.cpp

#include "Div.h"
using namespace std;

Div::Div():Sub("","",""){} // calls inherited Sub constructor

Div::Div(string para1, string para2, string para3):Sub(para1, para2, para3){
}

// creating a new Div object based on the provided string stream    
Instruction * Div::clone(stringstream & ss)
{
    Div* div = new Div();
    div->initialize(ss);
    return div;
}

// processing of addition functionality, using initializer from Sub and doing appropriate parsing
void Div::process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec)
{
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    
	param1 = Sub::param1; // parameters set through Sub's initializer
	param2 = Sub::param2;
	param3 = Sub::param3;
	
	//temp var to save map value for param. Keep param same so can update value from map when jump makes the instructions run again
	if(param2.at(0)=='$') varParam2=varMap[param2].first;
    else varParam2.assign(param2);
    if(param3.at(0)=='$') varParam3=varMap[param3].first;
    else varParam3.assign(param3);
	
	if(varParam3!="0"){
	double temp = stof(varParam2)/stof(varParam3); // division of two parameters
    varMap[param1].first=to_string(temp);    // pushes newly assigned variable back to varMap
	} else err<<"Can't divide by zero"<<endl;
}

string Div::getName(){return "";}


Div::~Div(){}; //Destructor