#ifndef THREADRUNNER_H
#define THREADRUNNER_H
#include "common.h"
#include "Instruction.h"
//#include "Parser.h"
#include "Thread.h"

//#include "TCPSocket.h"
//#include "includes.h"
// A class representing a single connection form a client
class ThreadRunner : public Thread //Inherit from Thread
{
 private:
 	vector<Instruction*> *threadedInstVec;
 	unordered_map<string, pair<string,string>> *varMap;

 public:
 ThreadRunner(vector<Instruction*>* t, unordered_map<string, pair<string,string>>* v); // Constructor: Set client connected TCP socket
 void * threadMainBody (void * arg); // Main thread body that serves the connection
//Garbage Collector
 ~ThreadRunner(); // Destructor
};

#endif