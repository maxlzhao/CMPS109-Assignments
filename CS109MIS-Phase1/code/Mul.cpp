// Mul.cpp

#include "Mul.h"

using namespace std;
  
// creating a new Mul object based on the provided string stream    
Instruction* Mul::clone(stringstream& ss){
    Mul* mul = new Mul();
    mul->initialize(ss);
    return mul;
}

// parses and initializes variables in Mul
void Mul::initialize (stringstream& ss){
    ofstream err;
    err.open("MIS.err", std::ios_base::app);
    int counter = 1;
    string str = "";
    getline(ss, str, ',');
    param1.assign(str);      // assigns parameter to store product in 
    getline(ss, str, ',');
    while(!ss.eof()) {       // creates parameter vector to store variables/constant to be multiplied
        if(counter >= 13){
            err << "Exceeded number of parameters for Mul" << endl;
            break;
        }
        paramVec.push_back(str);
        getline(ss, str, ',');
        counter++;
    }
    paramVec.push_back(str);
}

void Mul::process(unordered_map<string, pair<string,string>>& varMap,vector<Instruction*>& instVec){
    double product = 1;
    for(auto it = paramVec.begin(); it!= paramVec.end(); it++){ // iterates through parameter vector and multiplies accordingly
        if((*it).at(0) == '$'){             // if parameter is a variable, get value from map
           varParam = varMap[(*it)].first;
        }else{
            varParam = *it;
        }
         // multiply parameter with previous product
        product *= stod(varParam);
    }
    if(varMap[param1].second == "NUMERIC") {    // if data type is NUMERIC, cast product as 8 byte integer
        varMap[param1].first=to_string((int64_t)product);
    }else{
         varMap[param1].first=to_string(product);
    }
}

string Mul::getName()
{
    return "";
}

