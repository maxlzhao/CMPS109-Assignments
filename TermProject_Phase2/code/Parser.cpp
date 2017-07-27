#include "Parser.h"
using namespace std;
Parser::Parser(){}

void Parser::parse(const vector<string>& stringVec, unordered_map<string, pair<string,string>>& varMap, unordered_map<string, Instruction*>& instMap,vector<Instruction*>& instVec)
{
	unordered_map<string, pair<string,string>>* tempMap = &varMap;
	
	if(remove("MIS.err")!=0) perror("error deleting mis.err");
	else puts("file deleted");
	
	ofstream err;
	err.open("MIS.err", ios::out | ios::app | ios::binary);
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
	instMap["THREAD_BEGIN"] = new ThreadBegin();
	instMap["THREAD_END"] = new ThreadEnd();

    // cout<<"parse here"<<endl;
	string line= ""; //reading lines from text file
	//ifstream readFile(file);
	string name = ""; //string for instruction type
	vector<Instruction*> tempVec;
	vector<Instruction*> zeroVec;
	vector<vector<Instruction*>> resultVec;
	bool inThread = false;

	for(auto it = stringVec.begin(); it != stringVec.end(); it++) {
		stringstream iss(*it);
		getline(iss, name, ' '); 
		Instruction * inst = instMap[name]; //Object intialization
		if(inst !=NULL)
		{
			inst=inst->clone(iss);
			if(name.compare("LABEL")==0) { //if the name found in the parse is LABEL, inline it and set the line number
				//cout<<"Label"<<endl;
				inst->process(varMap, instVec);
			} 
			if(name.compare("THREAD_END") == 0){
				inThread = false;
				resultVec.push_back(tempVec);
				//for(auto &x:tempVec) cout << "TEMPVEC INSIDE FOR LOOP HAS: " << &x << endl;
				tempVec.clear();
			}
			if(!inThread){
				instVec.push_back(inst);
				zeroVec.push_back(inst);
			}else{
				instVec.push_back(inst);
				tempVec.push_back(inst);
			}
			if(name.compare("THREAD_BEGIN") == 0){
				inThread = true;
			}
			

			// instVec.push_back(inst); //push the instruction object into the instruction vector
		} else err << "Instruction not found in map: " <<name<< endl;
	}
		resultVec.push_back(zeroVec);
		// cout<<"parse still here"<<endl;

	for(auto itt = resultVec.begin(); itt != resultVec.end(); itt++){

		
		// ThreadRunner* me = new ThreadRunner(&tempVector,&varMap);
		// me->start();
	


			auto it = itt->begin();	//begin the loop of instructions
			cout << *it << endl;
			// cout<<instVec.size()<<endl;
			// cout<<instMap.size()<<endl;
			// cout<<varMap.size()<<endl;
			int jumpCounter = 0; //jump counter keeps track of the instruction line that we're at
			vector<double> differenceVec; //vector for checking for infinite loops
			while(it != itt->end()){
			    // cout<<*it<<endl;
				if(((*it)->getType()).compare("JMP") == 0)	//call function to check for if it's a JMP instruction
				{
					int itCount = stoi(varMap[(*it)->getName()].first);	//itCount stores the value of the LABEL line

					/////////// ERROR CHECK IF LABEL DOES NOT EXIST /////////////

					it = next(itt->begin(), itCount);	//iterator through the vector
					if(itCount < jumpCounter){							//if the LABEL line is before the JMP line, there will be an infinite loop
						err << "Infinite Loop from Jump" << endl;
						break;
					}
					jumpCounter = itCount;								//keep the jump counter up to date on where we are
					(*it)->process(varMap,*itt);
					it++;
				}else if(((*it)->getType()).compare("JMPGT") == 0) {	//checks if it's a JMPGT instruction. JMPLT,JMPGTE,JMPLTE have the same formate
					(*it)->process(varMap,*itt);	//calls the jmp
					float param2 = stof((*it)->getParam2()); //param2 stores the float of variable 2
					float param3 = stof((*it)->getParam3());//param 3 stores the float of variable 3
					if(param2 > param3) {	//if variable2>variable3, then we execute the following
						differenceVec.push_back(param2-param3); 	//push the difference of 2 and 3 in a vector
																	//we will use this to search for infinite loops
						int itCount = stoi(varMap[(*it)->getName()].first);	//set the LABEL line to itCount
						it = next(itt->begin(), itCount);	//iterate through the vector
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
						(*it)->process(varMap,*itt);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPGTE") == 0) {	//same as JMPGT format
					(*it)->process(varMap,*itt);
					float param2 = stof((*it)->getParam2());	
					float param3 = stof((*it)->getParam3());
					if(param2 >= param3) {	//if var2>= var3 execute the following
						differenceVec.push_back(param2-param3); 
						int itCount = stoi(varMap[(*it)->getName()].first); //set itCount
						it = next(itt->begin(), itCount);
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
						(*it)->process(varMap,*itt);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPLT") == 0)  { //same as JMPGT
					(*it)->process(varMap,*itt);
					float param2 = stof((*it)->getParam2());
					float param3 = stof((*it)->getParam3());
					if(param2 < param3) { //if var2<var3, execute	
						differenceVec.push_back(param2-param3); 
						int itCount = stoi(varMap[(*it)->getName()].first);
						it = next(itt->begin(), itCount);
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
						(*it)->process(varMap,*itt);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPLTE") == 0) { //same as JMPGT
					(*it)->process(varMap,*itt);
					float param2 = stof((*it)->getParam2());
					float param3 = stof((*it)->getParam3());
					//cout << "param2LTE: " << param2 << "param3LTE: " << param3 << endl;
					if(param2 <= param3) {
						differenceVec.push_back(param2-param3); 
						int itCount = stoi(varMap[(*it)->getName()].first);
						it = next(itt->begin(), itCount);
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
						(*it)->process(varMap,*itt);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPZ") == 0) { //if JMPZ or JMPNZ, only compare to 0
					(*it)->process(varMap,*itt);
					float param2 = stof((*it)->getParam2());
					if(param2==0) {	//if the parameter given is 0, execute
						differenceVec.push_back(param2); 
						int itCount = stoi(varMap[(*it)->getName()].first);
						it = next(itt->begin(), itCount);	//iterate through the vector
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
						(*it)->process(varMap,*itt);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPNZ") == 0) { //same as JMPZ
					(*it)->process(varMap,*itt);
					float param2 = stof((*it)->getParam2());
					if(param2!=0) {//if parameter 2 is not 0, execute the following
						differenceVec.push_back(param2); 
						int itCount = stoi(varMap[(*it)->getName()].first);
						it = next(itt->begin(), itCount);
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
}
	//readFile.close();
	// cout<<"YES"<<endl;
}


Parser::~Parser(){};