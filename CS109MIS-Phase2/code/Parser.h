#ifndef PARSER_H
#define PARSER_H
#include "common.h"
#include "TCPSocket.h"
#include "TCPServerSocket.h"
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
#include "ThreadBegin.h"
#include "ThreadEnd.h"
#include "ThreadRunner.h"
//#include "Connection.h"
//#include "GarbageCollector.h"
//#include "Thread.h"

class Parser
{
public:
    Parser(); //constructor
    void parse(const vector<string>& stringVec, unordered_map<string, pair<string,string>>& varMap, unordered_map<string, Instruction*>& instMap,vector<Instruction*>& instVec);
    ~Parser();
};
#endif

