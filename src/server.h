//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_SERVER_H
#define HTTP_FILE_SERVER_SERVER_H

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "connection_manager.h"

namespace Http {

    class Server {
    public:
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;

        Server(const std::string &host, const std::string &port, const std::string &work_dir);

        void run();
    private:
        /// Perform an asynchronous accept operation.
        void do_accept();

        /// Wait for a request to stop the server.
        void do_await_stop();

        /// The io_service used to perform asynchronous operations.
        boost::asio::io_service io_service_;

        /// The signal_set is used to register for process termination notifications.
        boost::asio::signal_set signals_;

        /// Acceptor used to listen for incoming connections.
        boost::asio::ip::tcp::acceptor acceptor_;

        /// The connection manager which owns all live connections.
        ConnectionManager connection_manager_;

        /// The next socket to be accepted.
        boost::asio::ip::tcp::socket socket_;

        /// The handler for all incoming requests.
        RequestHandler request_handler_;
    };
}


#endif //HTTP_FILE_SERVER_SERVER_H
