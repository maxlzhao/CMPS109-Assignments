//Jmplte.cpp

#include "Jmplte.h"

Jmplte::Jmplte():Jmpgt("","",""){}

Jmplte::Jmplte(string l, string p2, string p3):Jmpgt(l,p2,p3){}

Instruction* Jmplte::clone(stringstream& ss)
{
    Jmplte* jmplte = new Jmplte();
    jmplte->initialize(ss);
    return jmplte;
}

void Jmplte::process(unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec)
{
    //initialize param with those of jmpgt's param
    labelName.assign(Jmpgt::labelName);
    param2.assign(Jmpgt::param2);
    param3.assign(Jmpgt::param3);
    
    //update param val from 
    if(param2.at(0)=='$') varParam2=varMap[param2].first;
    else varParam2.assign(param2);
    if(param3.at(0)=='$') varParam3=varMap[param3].first;
    else varParam3.assign(param3);
}

string Jmplte::getName()
{
    return labelName;
}

string Jmplte::getType()
{
    return "JMPLTE";
}

string Jmplte::getParam2()
{
    return varParam2;
}

string Jmplte::getParam3()
{
    return varParam3;
}

Jmplte::~Jmplte(){}