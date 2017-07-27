//Jmpz.cpp
#include "Jmpz.h"

Jmpz::Jmpz():Jmpz("",""){}

Jmpz::Jmpz(string l, string c):labelName(l),param2(c),Instruction(){}

Instruction* Jmpz::clone(stringstream &ss)
{
    Jmpz* jmpz = new Jmpz();
    jmpz->initialize(ss);
    return jmpz;
}

void Jmpz::initialize(stringstream &ss)
{
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    string str = "";
    getline(ss,str,',');
    labelName.assign(str);
    getline(ss,str,',');
    //need to take into account constants
    param2.assign(str);
    //cout << "param2 is: " << param2 << endl;
    getline(ss,str);
    //cout << "str is: " << str << endl;
    if(!str.compare(param2) == 0){
        err << "Invalid number of parameters for Jmpz/Jmpnz" << endl;
    }
}

void Jmpz::process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec)
{
    //update val from map if param is variable
    if(param2.at(0)=='$') varParam2=varMap[param2].first;
    //else set param to const
    else varParam2=param2;
}

string Jmpz::getName()
{
    return labelName;
}

string Jmpz::getType()
{
    return "JMPZ";
}

string Jmpz::getParam2()
{
    return varParam2;
}

Jmpz::~Jmpz(){}