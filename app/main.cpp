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

void ourLibTest()
{
    printf("OurLib Test\n");

    Hello helloObj = Hello();
    helloObj.title = "Hello, from RestApp-Backend!";
    helloObj.print(std::cout);
}

void jwtTest()
{
    printf("JWT Test - https://github.com/Thalhammer/jwt-cpp/tree/master/example\n");

    // Create a new token with HS256 algorithm
    auto key = "good-secret";

    auto token = jwt::create()
                     .set_issuer("auth0")
                     .set_type("JWS")
                     .set_payload_claim("sample", jwt::claim(std::string("test")))
                     .sign(jwt::algorithm::hs256{key});

    std::cout << token << std::endl;

    // Verify the token
    try
    {
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{key})
                            .with_issuer("auth0");
        verifier.verify(decoded);
        std::cout << "Verified token" << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Error verifying token: " << e.what() << std::endl;
    }

    // Decode the token
    std::string token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJpc3MiOiJhdXRoMCIsInNhbXBsZSI6InRlc3QifQ.lQm3N2bVlqt2-1L-FsOjtR6uE-L4E9zJutMWKIe1v1M";
    auto decoded = jwt::decode(token);

    for (auto &e : decoded.get_payload_json())
        std::cout << e.first << " = " << e.second << std::endl;
}

void sqlpp11Test()
{
    printf("SQLpp11 Test - https://github.com/rbock/sqlpp11/tree/main/examples/connection_pool\n");

    // Initialize the global connection variable
    auto config = std::make_shared<sqlpp::postgresql::connection_config>();
    config->dbname = "restapp";
    config->user = "restapp";
    config->password = "test123";
    config->host = "database";
    config->port = 5432;
    config->debug = true;
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
}

void beastBoostTest()
{
    printf("Beast Test - https://github.com/boostorg/beast/tree/develop/example/http/server/small\n");
    runServer(2, new char *[2]{"0.0.0.0", "80"});
}

int main(int argc, char *argv[])
{
    printf("Hello, from RestApp-Backend!\n");

    ourLibTest();
    jwtTest();
    beastBoostTest();

    return 0;
}
