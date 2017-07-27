//Jmpgte.cpp
#include "Jmpgte.h"
Jmpgte::Jmpgte():Jmpgt("","",""){}
//change constructor to be like jmpgt
Jmpgte::Jmpgte(string l, string p2, string p3):Jmpgt(l,p2,p3){}

Instruction* Jmpgte::clone(stringstream& ss)
{
    Jmpgte* jmpgte = new Jmpgte();
    jmpgte->initialize(ss);
    return jmpgte;  //return new jmpgte object
}

void Jmpgte::process(unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec)
{
    //set jmpgte protected vars from jmpgt's protected vars
    labelName = Jmpgt::labelName;
    param2 = Jmpgt::param2;
    param3 = Jmpgt::param3;
    
    //if param is variable, update value from map
    if(param2.at(0)=='$') varParam2.assign(varMap[param2].first);
    //else set value to const
    else varParam2.assign(param2);
    if(param3.at(0)=='$') varParam3.assign(varMap[param3].first);
    else varParam3.assign(param3);
}

string Jmpgte::getName()
{
    return labelName;
}
string Jmpgte::getType()
{
    return "JMPGTE";
}

string Jmpgte::getParam2()
{
    return varParam2;
}

string Jmpgte::getParam3()
{
    return varParam3;
}

Jmpgte::~Jmpgte(){}