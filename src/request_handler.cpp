//
// Created by Дмитрий Брагин on 7/12/17.
//

#include <ios>
#include <sstream>
#include <fstream>
#include "request_handler.h"
#include "reply.h"
#include "request.h"
#include "MimeTypes.h"

namespace Http {

    RequestHandler::RequestHandler(const std::string &work_dir_path)
        : work_directory(work_dir_path)
    {

    }

    void RequestHandler::handle_request(const Request &req, Reply &rep) {
        // Decode url to path.
        std::string request_path;
        if (!url_decode(req.uri, request_path))
        {
            rep = Reply::stock_reply(Reply::bad_request);
            return;
        }

        // Request path must be absolute and not contain "..".
        if (request_path.empty() || request_path[0] != '/'
            || request_path.find("..") != std::string::npos)
        {
            rep = Reply::stock_reply(Reply::bad_request);
            return;
        }

        // If path ends in slash (i.e. is a directory) then add "index.html".
        if (request_path[request_path.size() - 1] == '/')
        {
            request_path += "index.html";
        }

        // Determine the file extension.
        std::size_t last_slash_pos = request_path.find_last_of("/");
        std::size_t last_dot_pos = request_path.find_last_of(".");
        std::string extension;
        if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
        {
            extension = request_path.substr(last_dot_pos + 1);
        }

        // Open the file to send back.
        std::string full_path = work_directory + request_path;
        std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
        if (!is)
        {
            rep = Reply::stock_reply(Reply::not_found);
            return;
        }

        // Fill out the reply to be sent to the client.
        rep.status = Reply::ok;
        char buf[512];
        while (is.read(buf, sizeof(buf)).gcount() > 0)
            rep.content.append(buf, is.gcount());
        rep.headers.resize(2);
        rep.headers[0].name = "Content-Length";
        rep.headers[0].value = std::to_string(rep.content.size());
        rep.headers[1].name = "Content-Type";
        rep.headers[1].value = MimeTypes::extension_to_type(extension);
    }

    bool RequestHandler::url_decode(const std::string &in, std::string &out) {
        out.clear();
        out.reserve(in.size());
        for (std::size_t i = 0; i < in.size(); ++i)
        {
            if (in[i] == '%')
            {
                if (i + 3 <= in.size())
                {
                    int value = 0;
                    std::istringstream is(in.substr(i + 1, 2));
                    if (is >> std::hex >> value)
                    {
                        out += static_cast<char>(value);
                        i += 2;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else if (in[i] == '+')
            {
                out += ' ';
            }
            else
            {
                out += in[i];
            }
        }
        return true;
    }

}
