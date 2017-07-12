//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_REQUEST_HANDLER_H
#define HTTP_FILE_SERVER_REQUEST_HANDLER_H


#include <string>

namespace Http {

    struct Reply;
    struct Request;

    class RequestHandler {
    public:
        RequestHandler(const RequestHandler &) = delete;
        RequestHandler& operator=(const RequestHandler &) = delete;

        explicit RequestHandler(const std::string &doc_root);

        void handle_request(const Request &request, Reply &reply);
    private:

        std::string doc_root;
        static bool url_decode(const std::string &in, std::string &out);


    };

}

#endif //HTTP_FILE_SERVER_REQUEST_HANDLER_H
