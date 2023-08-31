#ifndef SQLHANDLE
#define SQLHANDLE

#include <iostream>


/*#include <boost/asio/io_context.hpp>
#include <boost/mysql.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/system/system_error.hpp>
#include <string>
#include <memory>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
*/

/*plan
simple tcp connection ->
boost connection*/

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

enum class ConnectOptions
{
    host_name, 
    user_name,
    port,
    password,
};

class SQLHandler{
    sql::Driver * m_driver;
    sql::Connection * m_con;
    sql::Statement * m_stmt;
    sql::ResultSet * m_res;
    sql::ConnectOptionsMap m_connection_properties;
public:
    SQLHandler();
    ~SQLHandler();
    uint8_t get_driver();
    void set_properties(const ConnectOptions &option, const std::string &value); 
    void connect();      
};



#endif