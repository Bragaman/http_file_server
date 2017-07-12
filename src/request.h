//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_REQUEST_H
#define HTTP_FILE_SERVER_REQUEST_H

#include <string>
#include <vector>
#include "header.h"


namespace Http {

    struct Request
    {
        std::string method;
        std::string uri;
        int http_version_major;
        int http_version_minor;
        std::vector<Header> headers;
    };

}


#endif //HTTP_FILE_SERVER_REQUEST_H
