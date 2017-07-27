//Jmpnz.cpp

#include "Jmpnz.h"

Jmpnz::Jmpnz():Jmpz("",""){}

Jmpnz::Jmpnz(string l, string c):Jmpz(l,c){}

Instruction * Jmpnz::clone(stringstream &ss)
{
    Jmpnz* jmpnz = new Jmpnz();
    jmpnz->initialize(ss);
    return jmpnz;
}

void Jmpnz::process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec)
{
    //set param from jmpz's param
    labelName = Jmpz::labelName;
    param2 = Jmpz::param2;
    
    //update param val from varMap if its a variable
    if(param2.at(0)=='$') varParam2=varMap[param2].first;
    //else set to constant
    else varParam2=param2;
}

string Jmpnz::getName()
{
    return labelName;
}

string Jmpnz::getType()
{
    return "JMPNZ";
}

string Jmpnz::getParam2()
{
    return varParam2;
}

Jmpnz::~Jmpnz(){}