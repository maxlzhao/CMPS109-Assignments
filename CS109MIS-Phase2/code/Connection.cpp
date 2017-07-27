#include "Connection.h"
#include "common.h"
using namespace std;
//Constructor: Call parent Thread Constructor
Connection::Connection(TCPSocket * p_tcpSocket): Thread()
{
 tcpSocket = p_tcpSocket; // Set the TCP socket
 next_connection = NULL; // Set the next pointer to NULL
}
// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){next_connection = connection;}
// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){return next_connection;}
// Destructor: delete the TCP socket if set
Connection::~Connection(){if ( tcpSocket != NULL ) delete (tcpSocket);}

void * Connection::threadMainBody(void *arg)
{
	// cout<<"threading body"<<endl;
	vector<string> stringVec;
	int maxBytes = 1024*1024; // size of buffer. if we want to increase buffer size, use long
	char buffer[maxBytes]; // alocat buffer of 1 K
	memset(buffer,0,maxBytes); // initialize it.
	int bytes_read = tcpSocket->readFromSocket(buffer, maxBytes); // read data from the socket
	// if returned number of bytes is bigger that zero then print information about client and themessage
	if ( bytes_read > 0 ){
		//printf ("Received Message from %s:%d\n",(char*)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port);
		char* temp;
		temp = strtok(buffer,"~");
		//cout<<"here"<<endl;
		while(temp != NULL) {
			string tempstr(temp);
			stringVec.push_back(tempstr);
			temp = strtok(NULL,"~");

		}
		// for(auto&x: stringVec) {
		// 	cout << x << endl;
		// }
	}else perror("Error Receiving Message:"); // else print error through perror.

	//cout<<"still here"<<endl;

	
	ofstream err;
	err.open("MIS.err", std::ios_base::app); // opens error file
	//ofstream outputFile("errors.err");
	unordered_map<string, pair<string, string>> varMap;
	//vector<class name w/template> resultVec;
	unordered_map<string, Instruction*> instMap;
	vector<Instruction*> instVec;

	vector<string> outVec;
	vector<string> errVec;
	
	Parser* parser = new Parser();
	parser->parse(stringVec, varMap, instMap, instVec); // calls parse function to separate instructions 


	// cout<<"still here"<<endl;
	string oline = "";
	ifstream readFile("MIS.out");
	while(getline(readFile,oline))
	{
		outVec.push_back(oline); // passes string back to outvec
	}

	readFile.close();
	// cout<<"how bout here"<<endl;
	string eline = "";
	ifstream readFile2("MIS.err");
	while(getline(readFile2, eline))
	{
		errVec.push_back(eline);
	}

	readFile2.close();

	string passOutstr = "";
	string passErrstr = "";

	if(!outVec.empty()) {
		passOutstr = outVec.at(0);
		for(auto it = outVec.begin()+1; it != outVec.end(); it++){
			passOutstr += '~'+(*it);  // combining out strings separated with a tilde into a cstring
		}
	}

	if(!errVec.empty()) {
		passErrstr = errVec.at(0);
		for(auto it = errVec.begin()+1; it != errVec.end(); it++){
			passErrstr += '~'+(*it); // combining err strings separated with a tilde into a cstring
		}
	}

	string overallStr = passOutstr +"@"+passErrstr+"@"; // separates outstring and errstring with an @ sign for future parsing

	// cout << "overallstr is: " << overallStr << endl;
	
	const void* myOverallstr = overallStr.c_str();

	// printf("%s\n",myOverallstr);
	
	send(tcpSocket->getSocket(),myOverallstr,overallStr.size(),0);

	err.close();

}