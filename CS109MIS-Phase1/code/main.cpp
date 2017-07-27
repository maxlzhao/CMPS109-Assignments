//main.cpp
#include "common.h"
//#include "Instruction.h"
#include "Var.h"
#include "Add.h"
#include "Mul.h"
#include "Sub.h"
#include "Div.h"
#include "Ssc.h"
#include "Gsc.h"
#include "Label.h"
#include "Sleep.h"
#include "Assign.h"
#include "Out.h"
#include "Jmp.h"
#include "Jmpz.h"
#include "Jmpnz.h"
#include "Jmpgt.h"
#include "Jmpgte.h"
#include "Jmplt.h"
#include "Jmplte.h"

// #include "DataType.cpp"

using namespace std;


void parse(const string& file, unordered_map<string, pair<string,string>>& varMap, unordered_map<string, Instruction*>& instMap, vector<Instruction*>& instVec);

int main(int argc, const char* argv[] )
{
	ofstream err;
	err.open("MIS.err", std::ios_base::app);
	//ofstream outputFile("errors.err");
	unordered_map<string, pair<string, string>> varMap;
	//vector<class name w/template> resultVec;
	unordered_map<string, Instruction*> instMap;
	vector<Instruction*> instVec;
	
	//check there is file
	if(argc > 1) {
		parse(argv[1], varMap, instMap, instVec);
	}else {
		err << "no file" << endl;
	}

	// for(auto it = varMap.cbegin(); it != varMap.cend(); it++){
	// 	cout << it->first << ": " << it->second.first << endl;
	// }

	return 0;

}

/******** PARSE VAR, MAKE DATATYPE OBJECT, STORE IN VARMAP *****/

void parse(const string& file, unordered_map<string, pair<string,string>>& varMap, unordered_map<string, Instruction*>& instMap,vector<Instruction*>& instVec)
{
	ofstream err;
	err.open("MIS.err", std::ios_base::app);
	int instCount=0;
	//adding instructions into instruction map
	instMap["VAR"] = new Var();
	instMap["ADD"] = new Add();
	instMap["MUL"] = new Mul();
	instMap["SUB"] = new Sub();
	instMap["DIV"] = new Div();
	instMap["ASSIGN"] = new Assign();
	instMap["OUT"] = new Out();
	instMap["SET_STR_CHAR"] = new Ssc();
	instMap["GET_STR_CHAR"] = new Gsc();
	instMap["LABEL"] = new Label();
	instMap["SLEEP"] = new Sleep();
	instMap["JMP"] = new Jmp();
	instMap["JMPZ"] = new Jmpz();
	instMap["JMPNZ"] = new Jmpnz();
	instMap["JMPGT"] = new Jmpgt();
	instMap["JMPLT"] = new Jmplt();
	instMap["JMPGTE"] = new Jmpgte();
	instMap["JMPLTE"] = new Jmplte();


	string line=""; //reading lines from text file
	ifstream readFile(file);
	string name = ""; //string for instruction type
	while(getline(readFile, line))
	{
		stringstream iss(line);
		getline(iss, name, ' '); 
		Instruction * inst = instMap[name]; //Object intialization
		if(inst !=NULL)
		{
			inst=inst->clone(iss);
			if(name.compare("LABEL")==0) { //if the name found in the parse is LABEL, inline it and set the line number
				//cout<<"Label"<<endl;
				inst->process(varMap, instVec);
			} 
			instVec.push_back(inst); //push the instruction object into the instruction vector
		} else err << "Instruction not found in map: " <<name<< endl;
	}
	auto it = instVec.begin();	//begin the loop of instructions
	int jumpCounter = 0; //jump counter keeps track of the instruction line that we're at
	vector<double> differenceVec; //vector for checking for infinite loops
	while(it != instVec.end()){
		if(((*it)->getType()).compare("JMP") == 0)	//call function to check for if it's a JMP instruction
		{
			int itCount = stoi(varMap[(*it)->getName()].first);	//itCount stores the value of the LABEL line
			it = next(instVec.begin(), itCount);	//iterator through the vector
			if(itCount < jumpCounter){							//if the LABEL line is before the JMP line, there will be an infinite loop
				err << "Infinite Loop from Jump" << endl;
				break;
			}
			jumpCounter = itCount;								//keep the jump counter up to date on where we are
			(*it)->process(varMap,instVec);
			it++;
		}else if(((*it)->getType()).compare("JMPGT") == 0) {	//checks if it's a JMPGT instruction. JMPLT,JMPGTE,JMPLTE have the same formate
			(*it)->process(varMap,instVec);	//calls the jmp
			float param2 = stof((*it)->getParam2()); //param2 stores the float of variable 2
			float param3 = stof((*it)->getParam3());//param 3 stores the float of variable 3
			if(param2 > param3) {	//if variable2>variable3, then we execute the following
				differenceVec.push_back(param2-param3); 	//push the difference of 2 and 3 in a vector
															//we will use this to search for infinite loops
				int itCount = stoi(varMap[(*it)->getName()].first);	//set the LABEL line to itCount
				it = next(instVec.begin(), itCount);	//iterate through the vector
				if(itCount < jumpCounter){	//if the label is before the jump, execute the following
					if(differenceVec.size() == 2) {	//if the vector has 2 elements, one from one loop and another from another loop
													//and they are greater than or equal to each other, that means there will be an infinite loop
													//because the parameters are either staying the same or getting farther apart.
						if(differenceVec.back() >= differenceVec.front()) {
							err << "Infinite Loop from JMPGT" << endl;
							break;
						}
						differenceVec.clear();	//clear the vector after full
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) {	//makes sure LABELs aren't processed again to avoid label updating
				(*it)->process(varMap,instVec);
			}
			it++;
		}else if(((*it)->getType()).compare("JMPGTE") == 0) {	//same as JMPGT format
			(*it)->process(varMap,instVec);
			float param2 = stof((*it)->getParam2());	
			float param3 = stof((*it)->getParam3());
			if(param2 >= param3) {	//if var2>= var3 execute the following
				differenceVec.push_back(param2-param3); 
				int itCount = stoi(varMap[(*it)->getName()].first); //set itCount
				it = next(instVec.begin(), itCount);
				if(itCount < jumpCounter){	//if label is before jmp, execute
					if(differenceVec.size() == 2) {
						if(differenceVec.back() >= differenceVec.front()) {
							err << "Infinite Loop from JMPGTE" << endl;
							break;
						}
						differenceVec.clear();//clear the vector after full
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) {
				(*it)->process(varMap,instVec);
			}
			it++;
		}else if(((*it)->getType()).compare("JMPLT") == 0)  { //same as JMPGT
			(*it)->process(varMap,instVec);
			float param2 = stof((*it)->getParam2());
			float param3 = stof((*it)->getParam3());
			if(param2 < param3) { //if var2<var3, execute	
				differenceVec.push_back(param2-param3); 
				int itCount = stoi(varMap[(*it)->getName()].first);
				it = next(instVec.begin(), itCount);
				if(itCount < jumpCounter){
					//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
					if(differenceVec.size() == 2) {
						if(differenceVec.back() <= differenceVec.front()) {
							err << "Infinite Loop from JMPLT" << endl;
							break;
						}
						differenceVec.clear();
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) {
				(*it)->process(varMap,instVec);
			}
			it++;
		}else if(((*it)->getType()).compare("JMPLTE") == 0) { //same as JMPGT
			(*it)->process(varMap,instVec);
			float param2 = stof((*it)->getParam2());
			float param3 = stof((*it)->getParam3());
			//cout << "param2LTE: " << param2 << "param3LTE: " << param3 << endl;
			if(param2 <= param3) {
				differenceVec.push_back(param2-param3); 
				int itCount = stoi(varMap[(*it)->getName()].first);
				it = next(instVec.begin(), itCount);
				if(itCount < jumpCounter){
					//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
					if(differenceVec.size() == 2) {
						if(differenceVec.back() <= differenceVec.front()) {
							err << "Infinite Loop from JMPLTE" << endl;
							break;
						}
						differenceVec.clear();
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) {
				(*it)->process(varMap,instVec);
			}
			it++;
		}else if(((*it)->getType()).compare("JMPZ") == 0) { //if JMPZ or JMPNZ, only compare to 0
			(*it)->process(varMap,instVec);
			float param2 = stof((*it)->getParam2());
			if(param2==0) {	//if the parameter given is 0, execute
				differenceVec.push_back(param2); 
				int itCount = stoi(varMap[(*it)->getName()].first);
				it = next(instVec.begin(), itCount);	//iterate through the vector
				if(itCount < jumpCounter){
					//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
					if(differenceVec.size() == 2) {
						if(differenceVec.back() == differenceVec.front()) {
							err << "Infinite Loop from JMPZ" << endl;
							break;
						}
						differenceVec.clear();
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) {
				(*it)->process(varMap,instVec);
			}
			it++;
		}else if(((*it)->getType()).compare("JMPNZ") == 0) { //same as JMPZ
			(*it)->process(varMap,instVec);
			float param2 = stof((*it)->getParam2());
			if(param2!=0) {//if parameter 2 is not 0, execute the following
				differenceVec.push_back(param2); 
				int itCount = stoi(varMap[(*it)->getName()].first);
				it = next(instVec.begin(), itCount);
				if(itCount < jumpCounter){
					//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
					if(differenceVec.size() == 2) {
						if(differenceVec.back() == differenceVec.front()) {
							err << "Infinite Loop from JMPNZ" << endl;
							break;
						}
						differenceVec.clear();
					}
				}
				jumpCounter = itCount;
			}
			if(((*it)->getType()).compare("LABEL") != 0) { //make sure label doesn't get updated
				(*it)->process(varMap,instVec);
			}
			it++;
		}else{
			if(((*it)->getType()).compare("LABEL") != 0) { //make sure label doesn't get updated
				(*it)->process(varMap,instVec);
			}
			it++;
		}
		jumpCounter++;
	}
	readFile.close();
}
