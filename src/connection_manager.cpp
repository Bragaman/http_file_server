//
// Created by Дмитрий Брагин on 7/12/17.
//

#include "connection_manager.h"

namespace Http {

    ConnectionManager::ConnectionManager() {

    }

    void ConnectionManager::start(ConnectionPtr c) {
        connections.insert(c);
        c->start();
    }

    void ConnectionManager::stop(ConnectionPtr c) {
        connections.erase(c);
        c->stop();
    }

    void ConnectionManager::stop_all() {
        for (auto c: connections) {
            c->stop();
        }
        connections.clear();
    }

}