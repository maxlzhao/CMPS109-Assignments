#include "ThreadRunner.h"
#include "common.h"
using namespace std;
//Constructor: Call parent Thread Constructor
ThreadRunner::ThreadRunner(vector<Instruction*>* t, unordered_map<string, pair<string,string>>* v): Thread()
{

	threadedInstVec = t; 
	varMap = v;
}
// A modifier that sets the pointer of the next connection

// Destructor: delete the TCP socket if set
ThreadRunner::~ThreadRunner(){
	if ( threadedInstVec != NULL ) delete (threadedInstVec);
	if ( varMap != NULL ) delete (varMap);


}

void * ThreadRunner::threadMainBody(void *arg)
{
	// cout << "I AM IN THREADRUNNER~!@~@~!@~!@!~@!~@!~@!~@!~@!~@~!@~!@!~" << endl;
	auto it = threadedInstVec->begin();	//begin the loop of instructions
			// cout<<instVec.size()<<endl;
			// cout<<instMap.size()<<endl;
			// cout<<varMap.size()<<endl;
			ofstream err;
			err.open("MIS.err", std::ios_base::app);
			int jumpCounter = 0; //jump counter keeps track of the instruction line that we're at
			vector<double> differenceVec; //vector for checking for infinite loops
				if(threadedInstVec->empty()){
					// cout << "threadedInstVec is empty" << endl;
				}
				
			while(it != threadedInstVec->end()){
				// cout << "**********************************" << endl;
				// cout << "I AM IN WHILE LOOP IN threadMainBody!@#!@#@!#!@#!@#!@" << endl;
			    // cout<<"are we here"<<endl;
				if(((*it)->getType()).compare("JMP") == 0)	//call function to check for if it's a JMP instruction
				{
					int itCount = stoi((*varMap)[(*it)->getName()].first);	//itCount stores the value of the LABEL line

					/////////// ERROR CHECK IF LABEL DOES NOT EXIST /////////////

					it = next(threadedInstVec->begin(), itCount);	//iterator through the vector
					if(itCount < jumpCounter){							//if the LABEL line is before the JMP line, there will be an infinite loop
						err << "Infinite Loop from Jump" << endl;
						break;
					}
					jumpCounter = itCount;								//keep the jump counter up to date on where we are
					(*it)->process(*varMap,*threadedInstVec);
					it++;
				}else if(((*it)->getType()).compare("JMPGT") == 0) {	//checks if it's a JMPGT instruction. JMPLT,JMPGTE,JMPLTE have the same formate
					(*it)->process(*varMap,*threadedInstVec);	//calls the jmp
					float param2 = stof((*it)->getParam2()); //param2 stores the float of variable 2
					float param3 = stof((*it)->getParam3());//param 3 stores the float of variable 3
					if(param2 > param3) {	//if variable2>variable3, then we execute the following
						differenceVec.push_back(param2-param3); 	//push the difference of 2 and 3 in a vector
																	//we will use this to search for infinite loops
						int itCount = stoi((*varMap)[(*it)->getName()].first);	//set the LABEL line to itCount
						it = next(threadedInstVec->begin(), itCount);	//iterate through the vector
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
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPGTE") == 0) {	//same as JMPGT format
					(*it)->process(*varMap,*threadedInstVec);
					float param2 = stof((*it)->getParam2());	
					float param3 = stof((*it)->getParam3());
					if(param2 >= param3) {	//if var2>= var3 execute the following
						differenceVec.push_back(param2-param3); 
						int itCount = stoi((*varMap)[(*it)->getName()].first); //set itCount
						it = next(threadedInstVec->begin(), itCount);
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
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPLT") == 0)  { //same as JMPGT
					(*it)->process(*varMap,*threadedInstVec);
					float param2 = stof((*it)->getParam2());
					float param3 = stof((*it)->getParam3());
					if(param2 < param3) { //if var2<var3, execute	
						differenceVec.push_back(param2-param3); 
						int itCount = stoi((*varMap)[(*it)->getName()].first);
						it = next(threadedInstVec->begin(), itCount);
						if(itCount < jumpCounter){
							//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
							if(differenceVec.size() == 2) {
								if(differenceVec.back() >= differenceVec.front()) {
									err << "Infinite Loop from JMPLT" << endl;
									break;
								}
								differenceVec.clear();
							}
						}
						jumpCounter = itCount;
					}
					if(((*it)->getType()).compare("LABEL") != 0) {
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPLTE") == 0) { //same as JMPGT
					(*it)->process(*varMap,*threadedInstVec);
					float param2 = stof((*it)->getParam2());
					float param3 = stof((*it)->getParam3());
					//cout << "param2LTE: " << param2 << "param3LTE: " << param3 << endl;
					if(param2 <= param3) {
						differenceVec.push_back(param2-param3); 
						int itCount = stoi((*varMap)[(*it)->getName()].first);
						it = next(threadedInstVec->begin(), itCount);
						if(itCount < jumpCounter){
							//cout << differenceVec.back() << ": " << differenceVec.front() << endl;
							if(differenceVec.size() == 2) {
								if(differenceVec.back() >= differenceVec.front()) {
									err << "Infinite Loop from JMPLTE" << endl;
									break;
								}
								differenceVec.clear();
							}
						}
						jumpCounter = itCount;
					}
					if(((*it)->getType()).compare("LABEL") != 0) {
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPZ") == 0) { //if JMPZ or JMPNZ, only compare to 0
					(*it)->process(*varMap,*threadedInstVec);
					float param2 = stof((*it)->getParam2());
					if(param2==0) {	//if the parameter given is 0, execute
						differenceVec.push_back(param2); 
						int itCount = stoi((*varMap)[(*it)->getName()].first);
						it = next(threadedInstVec->begin(), itCount);	//iterate through the vector
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
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else if(((*it)->getType()).compare("JMPNZ") == 0) { //same as JMPZ
					(*it)->process(*varMap,*threadedInstVec);
					float param2 = stof((*it)->getParam2());
					if(param2!=0) {//if parameter 2 is not 0, execute the following
						differenceVec.push_back(param2); 
						int itCount = stoi((*varMap)[(*it)->getName()].first);
						it = next(threadedInstVec->begin(), itCount);
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
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}else{
					if(((*it)->getType()).compare("LABEL") != 0) { //make sure label doesn't get updated
						(*it)->process(*varMap,*threadedInstVec);
					}
					it++;
				}
				jumpCounter++;
			}
	
	err.close();

}