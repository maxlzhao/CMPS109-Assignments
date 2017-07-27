#include "Var.h"
// #include "DataType.cpp"
using namespace std;

Var::Var():Var("","","",""){} // default constructor to pass to parameterized constructor


Var::Var(string s_stringN, string s_stringT, string s_defaultVal, string s_size): // parameterized constructor
stringN(s_stringN), stringT(s_stringT), defaultVal(s_defaultVal), size(s_size), Instruction(){}


// creating a new Var object based on the provided string stream    
Instruction* Var::clone(stringstream& ss){
    Var* var = new Var();
    var->initialize(ss);
    return var;
}

// parses and initializes parameters for Var object
void Var::initialize (stringstream& ss){
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    string str = "";
    getline(ss, str, ',');
    stringN = str; // sets name of variable
    getline(ss,str,',');
    stringT = str; // sets type of variable
    getline(ss,str,',');
    defaultVal = str; // sets value of variable
    getline(ss,str,',');
    if(str.empty()) { // if 4th parameter is empty, variable is not string
        size = "";    // empty size
    } else{
        size = defaultVal; // if variable is a string, size = 4th parameter
        defaultVal = str;
    }
    getline(ss,str,' ');
    if(!str.compare(" ")){
        err << "Invalid number of parameters for Var" << endl;
    }
}

// processing to create respective object variables based on parameter
void Var::process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec){
    if(stringT == "NUMERIC") {
        d = new NUMERIC(stringN, defaultVal); // creates new NUMERIC object
        pair<string, string>valTypePair (to_string((int64_t)d->getValue()), d->getType()); // creates pair with value and type
        pair<string, pair<string, string>>numPair (d->getName(), valTypePair);
        varMap.insert(numPair); // pushes variable name and pair into varMap
    }
    if(stringT == "REAL"){
        d = new REAL(stringN, defaultVal);  // creates REAL object
        pair<string, string>valTypePair (to_string(d->getValue()), d->getType()); // creates pair with value and type
        pair<string, pair<string, string>>numPair (d->getName(), valTypePair);
        varMap.insert(numPair); // pushes variable name and pair into varMap
    }
    if(stringT == "CHAR"){
        d = new CHAR(stringN, defaultVal); // creates CHAR object
        string s(1, d->getChar());
        pair<string, string>valTypePair (s, d->getType()); // creates pair with char and type
        pair<string, pair<string, string>>numPair (d->getName(), valTypePair);
        varMap.insert(numPair); // pushes variable name and pair into varMap
    }
    if(stringT == "STRING"){
        d = new STRING(stringN, defaultVal, size); // creates STRING object
        string s(d->getString());
        pair<string, string>valTypePair (s, d->getType()); // creates pair with string and type
        pair<string, pair<string, string>>numPair (d->getName(), valTypePair);
        varMap.insert(numPair); // pushes vairalbe name and pair into varMap
    }
   
}


string Var::getName()
{
    return "";
}

Var::~Var(){} // destructor
