//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_CONNECTION_H
#define HTTP_FILE_SERVER_CONNECTION_H

#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include "request_handler.h"
#include "request_parser.h"
#include "reply.h"
#include "request.h"

namespace Http {

    class ConnectionManager;

    class Connection : public std::enable_shared_from_this<Connection>{
    public:
        Connection(const Connection &) = delete;
        Connection& operator=(const Connection &) = delete;

        explicit Connection(boost::asio::ip::tcp::socket socket,
                            ConnectionManager& manager, RequestHandler& handler);

        /// Start the first asynchronous operation for the connection.
        void start();

        /// Stop all asynchronous operations associated with the connection.
        void stop();

    private:
        /// Perform an asynchronous read operation.
        void do_read();

        /// Perform an asynchronous write operation.
        void do_write();

        /// Socket for the connection.
        boost::asio::ip::tcp::socket socket;

        /// The manager for this connection.
        ConnectionManager& connection_manager;

        /// The handler used to process the incoming request.
        RequestHandler& request_handler;

        /// Buffer for incoming data.
        std::array<char, 8192> buffer;

        /// The incoming request.
        Request request;

        /// The parser for the incoming request.
        RequestParser request_parser;

        /// The reply to be sent back to the client.
        Reply reply;
    };

    typedef std::shared_ptr<Connection> ConnectionPtr;

}


#endif //HTTP_FILE_SERVER_CONNECTION_H
