//Instruction.h
//#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "common.h"
using namespace std;

class Instruction
{
protected:
public:
  Instruction(); // constructor
  virtual Instruction* clone(stringstream& ss) = 0; // pure virtual clone to be inherited by all children, return object of child class
  virtual void initialize(stringstream& ss) = 0;    // pure virtual intialize to be inherited by all children, initialize internal variable of objects
  virtual void process(unordered_map<string, pair<string, string>>& varMap,vector<Instruction*>& instVec) = 0; // pure virtual process to be inherited by all children, process the functionality of instructions
  virtual string getName()=0;
  virtual string getType()=0;
  virtual string getParam2(){"";}
  virtual string getParam3(){"";}
  virtual ~Instruction(); // desctructor
};

#endif