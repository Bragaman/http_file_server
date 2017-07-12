#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.h"

int main(int argc, char* argv[])
{
    try
    {
        // Check command line arguments.
        if (argc != 2)
        {
            std::cerr << "Usage: http_server on localhost <port>\n";
            return 1;
        }

        // Initialise the server.
        Http::Server s("localhost", argv[1], "");

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}