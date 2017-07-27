#ifndef HTTPIMAGESERVICE_H
#define HTTPIMAGESERVICE_H
#include "HTTPService.h"
#include "common.h"
// An HTTP Service that serves HTML files
class HTTPImageService: public HTTPService // Inherit from HTTPService Base class
{
    private:
        string image_mime_type;
    public:
        // Constructor, receiving file cache, resources to serve and a flag that enabled deleting the cache in the destructor
        HTTPImageService(FileCache * p_fileCache,string p_image_mime_type,bool p_clean_cache = true);
        // Execute the service and write back the results to the TCPSocket
        virtual bool execute(HTTPRequest * p_httpRequest,TCPSocket * p_tcpSocket);
        virtual HTTPService * clone (); // Clone and create a new object
        ~HTTPImageService(); // Destructor
};

#endif // HTTPIMAGESERVICE_H
