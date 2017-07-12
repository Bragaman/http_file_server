# http_file_server
Easy http async server on cpp14 and boost

Асинхронный сервер на boost::asio, порт задается аргументом командной строки.
Должен по запросу из строки браузера вида: 
`localhost:xxxx/get/file_name` вернуть файл с именем
`file_name` из рабочей директории или ошибку.


Основан на [примере из boost](http://www.boost.org/doc/libs/1_64_0/doc/html/boost_asio/examples/cpp11_examples.html#boost_asio.examples.cpp11_examples.http_server)
