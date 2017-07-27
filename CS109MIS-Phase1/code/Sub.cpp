// Sub.cpp

#include "Sub.h"

using namespace std;

Sub::Sub():Sub("","",""){}

// parametized constructor initialiing data members using attribute lists and invoking parent constructor
Sub::Sub(string para1, string para2, string para3):
    param1(para1), param2(para2), param3(para3), Instruction(){}
  
// creating a new Sub object based on the provided string stream    
Instruction* Sub::clone(stringstream& ss){
    Sub * sub = new Sub();
    sub->initialize(ss);
    return sub;
}

// parses and intializes parameters in Sub
void Sub::initialize (stringstream& ss){
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    string str = "";
    getline(ss, str, ',');
    param1.assign(str);   // parameter to store difference in 
    getline(ss,str,',');
    param2.assign(str);   // first parameter
    getline(ss,str,',');
    param3.assign(str);   // parameter to subtract
    getline(ss,str,' ');
    if(!str.compare(" ")){
        err << "Invalid number of parameters for Sub/Div" << endl;
    }

}

// processes and completes subtraction operation
void Sub::process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec){
    if(param2.at(0)=='$') varParam2.assign(varMap[param2].first);
    else varParam2.assign(param2);
    if(param3.at(0)=='$') varParam3.assign(varMap[param3].first);
    else varParam3.assign(param3);
    
    int temp=stof(varParam2)-stof(varParam3);   // subtracts third parameter from second parameter
    varMap[param1].first=to_string(temp); // pushes newly assigned difference variable back to varMap
}


string Sub::getName()
{
    return "";
}

Sub::~Sub(){} // destructor

