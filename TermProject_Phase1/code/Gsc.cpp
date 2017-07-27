//Gsc.cpp

#include "Gsc.h"

Gsc::Gsc():Ssc("",0,""){}; //call ssc constructor

Gsc::Gsc(string str, int i, string c):Ssc(str, i, c){}  //initialize gsc through ssc. won't have to call gsc intialize

void Gsc::process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVecc)
{
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    
	line = Ssc::line; //assign this objects variables to ssc variables
	index=Ssc::index;
	character=Ssc::character;

    if(varMap.count(line)==1) //if the string variable exists in the varMap, execute
    {
        string temp="";
        temp.assign(varMap[line].first);    //store the string variable in a temp
        if(index>=temp.size()) err<<"index out of range"<<endl;
        string a(1, temp[++index]);   //take the character at the index of the string
        varMap[character].first.assign(a);  //store character into 3rd variable
    } else {err<<"Key doesn't exist"<<endl;}
}

Instruction * Gsc::clone(stringstream& ss) //cloning for gsc
{
    Gsc* gsc = new Gsc();
    gsc->initialize(ss);
    return gsc;
}

string Gsc::getName() //virtual void function to get name (pure)
{
    return "";
}

Gsc::~Gsc(){}