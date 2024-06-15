#pragma once

#include <db_connection.h>

extern thread_local db_connection g_dbc;

void db_global_init(std::shared_ptr<sqlpp::mysql::connection_config> config);