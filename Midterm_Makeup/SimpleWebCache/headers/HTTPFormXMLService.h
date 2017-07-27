#ifndef HTTPFORMXMLSERVICE_H
#define HTTPFORMXMLSERVICE_H
#include "HTTPFormService.h"
// An HTTP Service that serves HTML Form posts and parses 
class HTTPFORMXMLService: public HTTPFORMService // Inherit from HTTPService Base class
{
    private:
        string compose_reply();
    public:
        // Constructor, receiving file cache, resources to serve and a flag that enabled deleting the cache in the destructor
        HTTPFORMXMLService();
        // Execute the service and write back the results to the TCPSocket
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone (); // Clone and create a new object
        ~HTTPFORMXMLService(); // Destructor
};

#endif // HTTPFORMXMLSERVICE_H
