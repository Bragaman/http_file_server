//
// Created by Дмитрий Брагин on 7/12/17.
//

#include "MimeTypes.h"
#include <map>

namespace Http {
    namespace MimeTypes {

        std::map<std::string, std::string> mapping = {
                {"gif",  "image/gif"},
                {"htm",  "text/html"},
                {"html", "text/html"},
                {"jpg",  "image/jpeg"},
                {"png",  "image/png"}
        };

        std::string extension_to_type(const std::string &extension) {
            try {
                return mapping.at(extension);
            } catch (std::out_of_range e) {
                return "text/plain";
            }
        }

    }
}