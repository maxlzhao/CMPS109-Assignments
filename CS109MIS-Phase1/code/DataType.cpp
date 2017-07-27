#include "common.h"
using namespace std;

// DataType creates the four data types to be created by VAR

class DataType{
	protected:
	public:
		DataType(){}; // default constructor
		virtual double getValue() = 0;
		virtual string getName() = 0;
		virtual string getType() = 0;
		virtual void updateValue(double updatedVal) = 0;
		virtual char getChar(){}
		virtual void updateChar(char updatedChar){}
		virtual void updateString(int index, char updatedChar){}
		virtual char* getString(){}
		~DataType(){}; // destructor
};


class NUMERIC: public DataType
{
private:
	string name;			// name of variable
	int64_t value;			// 8 byte non-decimal numeric value
public:
	NUMERIC(string name, string x):value(atoi(x.c_str())),name(name),DataType(){} // constructor to assign private variables
	virtual string getName() {return name;}
	virtual string getType() {return "NUMERIC";}
	double getValue() {return value;}
	void updateValue(double updatedVal) {value = updatedVal;}
	~NUMERIC(){} // default constructor
};


class REAL: public DataType 
{
private:
    string name;			// name of variable
	double value;			// 8 byte decimal numeric value
public:
	REAL(string name, string x):value(std::stod(x)),name(name),DataType(){} // constructor to assign private variables
	virtual string getName() {return name;}
	virtual string getType() {return "REAL";}
	double getValue() {return value;}
	void updateValue(double updatedVal) {value = updatedVal;}
	~REAL(){} // destructor
};


class CHAR: public DataType
{
private:
	string name;			// name of variable
	char x;					// 1 byte character
public:
	CHAR(string name, string x):name(name),x(x[1]),DataType(){} // constructor to assign private variables
	string getName() {return name;}
	virtual string getType() {return "CHAR";}
	void updateChar(char y) {x = y;}
	char getChar(){return x;}
	void updateValue(double updatedVal){} // unnecessary but implemented due to pure virtual method in DataType
	double getValue(){} // unnecessary but implemented due to pure virtual method in DataType
	~CHAR(){} // destructor
};


class STRING: public DataType
{
private:
	string name;			// name of variable
	char* charArray;		// pointer to character array of 1-256 bytes
public:
	// constructor to create char array of defined size and set private variables
	STRING(string name, string s, string size):name(name),DataType(){charArray = new char[atoi(size.c_str())]; strcpy(charArray, s.c_str());}
	string getName() {return name;}
	virtual string getType() {return "STRING";}
	char* getString() {return charArray;}
	void updateString(int index, char c) {charArray[index] = c;} // updates character index @ index w/ char c specified
	void updateValue(double updatedVal){} // unnecessary but implmemented due to pure virtual method in DataType
	double getValue(){} // unnecessary but implemented due to pure virtual method in DataType
	~STRING(){delete[] charArray;} // destructor
};
