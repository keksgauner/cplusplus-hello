#include <iostream>
#include <string>
#include <jwt-cpp/jwt.h>
#include "Hello.h"
#include <db_global.h>
#include <sqlpp11/postgresql/postgresql.h>
#include <sqlpp11/sqlpp11.h>
#include <memory>
#include <thread>
#include <http_server_small.h>

int main(int argc, char *argv[])
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
    auto config = std::make_shared<sqlpp::postgresql::connection_config>();
    config->dbname = "restapp";
    config->user = "restapp";
    config->password = "test123";
    config->host = "localhost";
    config->port = 5432;
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
        // Replace g_dbc with a valid class or namespace
        // For example:
        sqlpp::postgresql::connection dbc(config);
        dbc(select(sqlpp::value(1).as(sqlpp::alias::a)));
      } }));
    }
    for (auto &&t : threads)
    {
        t.join();
    }

    // Boost beast
    // Run the server
    runServer(argc, argv);

    return 0;
}
