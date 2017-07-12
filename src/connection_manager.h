//
// Created by Дмитрий Брагин on 7/12/17.
//

#ifndef HTTP_FILE_SERVER_CONNECTION_MANAGER_H
#define HTTP_FILE_SERVER_CONNECTION_MANAGER_H

#include <set>
#include "connection.h"

namespace Http {

    /// Manages open connections so that they may be cleanly stopped when the server
    /// needs to shut down.
    class ConnectionManager {
    public:
        ConnectionManager(const ConnectionManager &) = delete;
        ConnectionManager& operator=(const ConnectionManager &) = delete;

        ConnectionManager();

        /// Add the specified connection to the manager and start it.
        void start(ConnectionPtr c);

        /// Stop the specified connection.
        void stop(ConnectionPtr c);

        /// Stop all connections.
        void stop_all();
    private:
        std::set<ConnectionPtr> connections;
    };

}

#endif //HTTP_FILE_SERVER_CONNECTION_MANAGER_H
