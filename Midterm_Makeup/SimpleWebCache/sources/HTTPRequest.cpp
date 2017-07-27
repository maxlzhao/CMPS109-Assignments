#include "HTTPRequest.h" 
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
// Add header key/value fields to the header map
void HTTPRequest::addToHeaderMap(string header_item)
{
    // header_item is in the form of <key>: <value>\r\n
    stringstream iss(header_item); // stringstream for parsing a header item
    string key=""; // A string to store key value
    string value = ""; // A string to store value
    getline(iss,key,':'); // fetch key token before ':' character 
    getline(iss,value,'\r'); // fetch value token between ':' and '\r' characters 
    trim(value);
    header[key] = value;  // add to the map
}
// Constructor setting the target request TCPSocket
HTTPRequest::HTTPRequest(TCPSocket * p_tcpSocket)
{
    tcpSocket = p_tcpSocket; // Set tcpSocket data member
}

// Read the header from the socket and parse it. 
// Notice that a descendant class is instantiated based on the type of the method HTTPTransaction and hence some data were read from the socket and this is passed in initial_header
void HTTPRequest::readAndParse(string initial_header)
{
    char buffer[1024];// A buffer to read data in
    memset (buffer,1024,0); // Initialize buffer
    string http_stream=initial_header; // copy initial header into HTTP stream
    for ( ;http_stream.find("\r\n\r\n") ==std::string::npos; )
    { // keep on reading as long as we cannot find the "\r\n\r\n" of the header
        tcpSocket->readFromSocket(buffer,1023);
        http_stream +=buffer; // Append what you have got from the socket
        memset (buffer,0,1024); // Reinitialize the read buffer
    }
    stringstream iss(http_stream); // stringstream for parsing the header
    // Get method, URI, and protocol from the first line
    getline(iss,method,' '); 
    getline(iss,resource,' ');
    getline(iss,protocol,'\n');
    protocol.pop_back(); // protocol now has '\r' in it so we want to remove it

    string line = " "; // set line to anything
    for (;!line.empty();) // keep on looping until you get an empty line indicating "\r\n\r\n" was found
    {
        getline(iss,line,'\n'); // get token until '\n'
        line.pop_back(); // eat up the '\r'
        //cout << line << endl;
        // now we have the header item in line
        // if line is not empty then we did not reach the end of the header, so we parse rge item
        if ( !line.empty()) addToHeaderMap(line); 
    }
    // extract any data, that have been read from the socket, after the header and store it in body    
    getline(iss,line,'\n'); 
    body = line;

}
// Selector returning the resource URI of the header
string HTTPRequest::getResource ()
{
    return resource;
}

string HTTPRequest::getHeaderValue(string header_item_name)
{
    return header[header_item_name];
}

// A selector returning a reference to the body of the request
string & HTTPRequest::getBody()
{
    return body;
}
// Destructor
HTTPRequest::~HTTPRequest(){}
