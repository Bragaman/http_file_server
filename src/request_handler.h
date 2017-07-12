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

        explicit RequestHandler(const std::string &work_dir_path);

        void handle_request(const Request &request, Reply &reply);
    private:

        std::string work_directory;
        static bool url_decode(const std::string &in, std::string &out);


    };

}

#endif //HTTP_FILE_SERVER_REQUEST_HANDLER_H
