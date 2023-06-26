#pragma once

#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/mysql.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/system/system_error.hpp>
#include <string>
#include <memory>

class SQLHandler{
    boost::asio::io_context m_io_context;
    std::unique_ptr<boost::asio::ssl::context> m_ssl_context;
    std::unique_ptr<boost::mysql::tcp_ssl_connection> m_sql_connection; 
public:
    void m_sql_init();    
};