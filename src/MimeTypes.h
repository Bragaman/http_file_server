//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_MIMETYPES_H
#define HTTP_FILE_SERVER_MIMETYPES_H

#include <string>

namespace Http {
    namespace MimeTypes {
        /// Convert a file extension into a MIME type.
        std::string extension_to_type(const std::string& extension);
    }
}


#endif //HTTP_FILE_SERVER_MIMETYPES_H
