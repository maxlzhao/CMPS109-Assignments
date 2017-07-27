/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HTTPImageService.h
 * Author: Aou
 *
 * Created on December 1, 2016, 6:27 PM
 */

#ifndef HTTPIMAGESERVICE_H
#define HTTPIMAGESERVICE_H
#include "HTTPService.h"
// An HTTP Service that serves HTML files
class HTTPImageService: public HTTPService // Inherit from HTTPService Base class
{
    private:
    public:
        // Constructor, receiving file cache, resources to serve and a flag that enabled deleting the cache in the destructor
        HTTPImageService(FileCache * p_fileCache,bool p_clean_cache = true);
        // Execute the service and write back the results to the TCPSocket
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone (); // Clone and create a new object
        ~HTTPImageService(); // Destructor
};









#endif /* HTTPIMAGESERVICE_H */

