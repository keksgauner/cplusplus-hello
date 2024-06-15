#include <db_connection.h>

#include <sqlpp11/mysql/mysql.h>

static sqlpp::mysql::connection_pool g_db_pool{};

thread_local db_connection g_dbc{g_db_pool};

void db_global_init(std::shared_ptr<sqlpp::mysql::connection_config> config)
{
    g_db_pool.initialize(config, 5);
}