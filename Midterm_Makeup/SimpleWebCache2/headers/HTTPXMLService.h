/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HTTPXMLService.h
 * Author: Aou
 *
 * Created on December 1, 2016, 8:45 PM
 */

#ifndef HTTPXMLSERVICE_H
#define HTTPXMLSERVICE_H

#include "HTTPFormService.h"
// An HTTP Service that serves XML Form posts and parses 
class HTTPXMLService: public HTTPFORMService // Inherit from HTTPService Base class
{
    protected:
        string compose_reply(); // overwrites HTTPFORMService parent class's compose_reply
    public:
        // Constructor, receiving file cache, resources to serve and a flag that enabled deleting the cache in the destructor
        HTTPXMLService();
        // Execute the service and write back the results to the TCPSocket
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone (); // Clone and create a new object
        ~HTTPXMLService(); // Destructor
};




#endif /* HTTPXMLSERVICE_H */

