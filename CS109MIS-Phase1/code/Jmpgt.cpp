//Jmpgt.cpp

#include "Jmpgt.h"

Jmpgt::Jmpgt():Jmpgt("","",""){}

Jmpgt::Jmpgt(string l,string p2, string p3):labelName(l),param2(p2),param3(p3),Instruction(){}

Instruction * Jmpgt::clone(stringstream& ss)
{
    Jmpgt * jmpgt = new Jmpgt();
    jmpgt->initialize(ss);
    return jmpgt;   //return new jmpgt object
}
void Jmpgt::initialize(stringstream& ss)
{
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    //initialize param
    string str="";
    getline(ss,str,',');
    labelName.assign(str);
    getline(ss,str,',');
    param2.assign(str);
    getline(ss,str,',');
    param3.assign(str);
    getline(ss,str);
    if(!str.compare(param3)==0) {
        err << "Invalid number of parameters for Jmpgt/Jmpgte/Jmplt/Jmplte" << endl;
    }
}

void Jmpgt::process( unordered_map<string, pair<string,string>>& varMap, vector<Instruction*>& instVec)
{
    //if param is a var, update value of param from varMap
    if(param2.at(0)=='$') varParam2.assign(varMap[param2].first);
    //else just set param to be the string constant
    else varParam2.assign(param2);
    if(param3.at(0)=='$') varParam3.assign(varMap[param3].first);
    else varParam3.assign(param3);
}
string Jmpgt::getType()
{
    return "JMPGT";
}
string Jmpgt::getParam2()
{
    return varParam2;   //return param
}

string Jmpgt::getParam3()
{
    return varParam3;   //return param
}

string Jmpgt::getName(){
    return labelName;
}

Jmpgt::~Jmpgt(){}