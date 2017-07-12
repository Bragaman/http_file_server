//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_HEADER_H
#define HTTP_FILE_SERVER_HEADER_H

#include <string>

namespace Http {

    struct Header
    {
        std::string name;
        std::string value;
    };

}

#endif //HTTP_FILE_SERVER_HEADER_H
