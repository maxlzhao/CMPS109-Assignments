#include "TCPSocket.h"

using namespace std;

int main (int argc,char ** argv)
{

	if ( argc != 3) { // Check on the number of arguments and exit if incorrect
		printf ("Usage: ./client <server-address> <file> \n");
	}	

	TCPSocket client((char*)"127.0.0.1",9999,-1,-1); // creates new client under port 9999 and address 127.0.0.1

	vector<string> stringVec;

	//make function to return constant void pointer to send over socket
	ifstream readFile(argv[2]);
	string name = "";
	string line = "";
	while(getline(readFile,line))
	{
		stringVec.push_back(line);
	}


	string passstr = stringVec.at(0);
	for(auto it = stringVec.begin()+1; it != stringVec.end(); it++){
		passstr += '~'+(*it);
	}
	const void* mystr = passstr.c_str();
	if ( argc != 3) { // Check on the number of arguments and exit if incorrect
		printf ("Usage: ./client <server-address> <file> \n");
		exit(1);
	}
	
	send(client.getSocket(),mystr,passstr.size(),0);
		//close(sock);// Close the socket.

	vector<string> outVec;
	vector<string> errVec;

	char* tempOut;
	char* tempErr;
	int maxBytes = 1000000; // size of buffer
	char buffer[maxBytes]; // alocat buffer of 1 K
	memset(buffer,0,maxBytes); // initialize it.
	int bytes_read = client.readFromSocket(buffer, maxBytes); // read data from the socket
	//cout << buffer << endl;
	// if returned number of bytes is bigger that zero then print information about client and themessage
	if ( bytes_read > 0 ){
		//printf ("Received Message from %s:%d\n",(char*)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port);
		char* temp;
		char* temp1;
		//cout << "BUFFER HAS*********************" << buffer << endl;
		temp = strtok(buffer,"@");
		temp1 = strtok(NULL,"@");
		//cout << "orignal temp has: " << temp << endl;
		bool isOut = true;
		// cout << "before the while loop" << endl;

		
		//cout << "in isOut loop" << endl;
		char* temp2;
		temp2 = strtok(temp,"~");
		while(temp2 != NULL) {
			string tempstr(temp2);
			outVec.push_back(tempstr);
			// cout <<"temp str is : " << tempstr << endl;
			temp2 = strtok(NULL,"~"); // parses by tildes in outvec
		}
	
		char* temp3;
		temp3 = strtok(temp1,"~");
		while(temp3 != NULL) {
			string temp2str(temp3);
			// cout << "TEMP STR I@@@@@@@@@@@@@@@@@@@@@@@@@@@N ERR IS: " << temp2str << endl;
			errVec.push_back(temp2str);
			temp3 = strtok(NULL,"~"); // parses by tildes in errvec
		}

		// for(auto it = errVec.begin(); it!= errVec.end(); it++) {
		// 	cout << *it << endl;
		// }
	
	}else perror("Error Receiving Message:"); // else print error through perror.


	if(remove("MISclient.out")!=0) perror("failed to delete MISclient.out");
    else puts("file deleted");

	ofstream out;
	out.open("MISclient.out", std::ios_base::app);

	if(!outVec.empty()){
		for(auto&x: outVec) {
			out << x << endl; // pushes all output in outvec into output file
		}
	}	

	out.close();


	if(remove("MISclient.err")!=0) perror("failed to delete MISclient.err");
    else puts("file deleted");

	ofstream err;
	err.open("MISclient.err", std::ios_base::app);

	if(!errVec.empty()){
		for(auto&y: errVec) {
			err << y << endl; // pushes all errors in errvec into error file
		}
	}	

	err.close();

	cout << "finished" << endl;
}

