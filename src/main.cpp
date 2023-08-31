#include <iostream>
#include "web_request.h"
#include "logger.h"
#include "sql.h"
#define DEBUG_VERSION 


int main()
{
    SQLHandler m_sql;
    uint8_t ret = m_sql.get_driver();
    m_sql.set_properties(ConnectOptions::host_name, "tcp://127.0.0.1");
    m_sql.set_properties(ConnectOptions::password, "root");
    m_sql.set_properties(ConnectOptions::port, "3306");
    m_sql.set_properties(ConnectOptions::user_name, "root");
    m_sql.connect();
    return 0;
}
