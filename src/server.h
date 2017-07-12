//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_SERVER_H
#define HTTP_FILE_SERVER_SERVER_H

#include <string>

namespace Http {

    class Server {
    public:
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        Server(const std::string &host, const std::string &port);

        void run();
    private:
    };
}


#endif //HTTP_FILE_SERVER_SERVER_H
