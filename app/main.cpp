#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <jwt-cpp/jwt.h>
#include "Hello.h"
#include <sqlpp11/mysql/mysql.h>

int main(int, char **)
{
    printf("Hello, from DeePay-Backend!\n");

    // Our lib
    Hello helloObj = Hello();
    helloObj.title = "Hello, from DeePay-Backend!";
    helloObj.print(std::cout);

    // jwt example
    std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJhdXRoMCIsInNhbXBsZSI6InRlc3QifQ.lQm3N2bVlqt2-1L-FsOjtR6uE-L4E9zJutMWKIe1v1M";
    auto decoded = jwt::decode(token);

    for (auto &e : decoded.get_payload_json())
        std::cout << e.first << " = " << e.second << std::endl;

    // sqlpp11
    // Initialize the global connection variable
    auto config = std::make_shared<sqlpp::mysql::connection_config>();
    config->dbname = "restapp";
    config->user = "restapp";
    config->password = "test123";
    config->debug = false;
    db_global_init(config);

    // Spawn 10 threads and make them send SQL queries in parallel
    int num_threads = 10;
    int num_queries = 5;
    std::vector<std::thread> threads{};
    for (int i = 0; i < num_threads; ++i)
    {
        threads.push_back(std::thread([&]()
                                      {
      for (int j = 0; j < num_queries; ++j)
      {
        g_dbc(select (sqlpp::value (1).as(sqlpp::alias::a)));
      } }));
    }
    for (auto &&t : threads)
    {
        t.join();
    }

    // Boost Beast
    try
    {
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: " << argv[0] << " <address> <port>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80\n";
            return EXIT_FAILURE;
        }

        auto const address = net::ip::make_address(argv[1]);
        unsigned short port = static_cast<unsigned short>(std::atoi(argv[2]));

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        tcp::socket socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
