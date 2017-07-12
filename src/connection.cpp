//
// Created by Дмитрий Брагин on 7/12/17.
//

#include "connection.h"
#include "reply.h"
#include "connection_manager.h"

namespace Http {

    Connection::Connection(boost::asio::ip::tcp::socket socket, ConnectionManager &manager, RequestHandler &handler)
            : socket(std::move(socket)),
              connection_manager(manager),
              request_handler(handler) {

    }

    void Connection::start() {
        do_read();
    }

    void Connection::stop() {
        socket.close();
    }

    void Connection::do_read() {
        auto self(shared_from_this());
        socket.async_read_some(boost::asio::buffer(buffer),
                               [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                                   if (!ec) {
                                       RequestParser::ResultType result;
                                       std::tie(result, std::ignore) = request_parser.parse(
                                               request, buffer.data(), buffer.data() + bytes_transferred);

                                       if (result == RequestParser::good) {
                                           request_handler.handle_request(request, reply);
                                           do_write();
                                       } else if (result == RequestParser::bad) {
                                           reply = Reply::stock_reply(Reply::bad_request);
                                           do_write();
                                       } else {
                                           do_read();
                                       }
                                   } else if (ec != boost::asio::error::operation_aborted) {
                                       connection_manager.stop(shared_from_this());
                                   }
                               });
    }

    void Connection::do_write() {
        auto self(shared_from_this());
        boost::asio::async_write(socket, reply.to_buffers(),
                                 [this, self](boost::system::error_code ec, std::size_t) {
                                     if (!ec) {
                                         // Initiate graceful connection closure.
                                         boost::system::error_code ignored_ec;
                                         socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                                         ignored_ec);
                                     }

                                     if (ec != boost::asio::error::operation_aborted) {
                                         connection_manager.stop(shared_from_this());
                                     }
                                 });
    }
}
