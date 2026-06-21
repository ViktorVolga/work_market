#pragma once

#include <boost/mysql/connection.hpp>
#include <boost/mysql/diagnostics.hpp>
#include <boost/mysql/error_code.hpp>
#include <boost/mysql/error_with_diagnostics.hpp>
#include <boost/mysql/handshake_params.hpp>
#include <boost/mysql/results.hpp>
#include <boost/mysql/row_view.hpp>
#include <boost/mysql/statement.hpp>
#include <boost/mysql/tcp_ssl.hpp>
#include <boost/mysql/throw_on_error.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>

#include <iostream>
#include "logger.h"

using boost::mysql::error_code;

class SQL_IO{
    boost::asio::ip::tcp::resolver::results_type m_endpoint;
    std::unique_ptr<boost::mysql::handshake_params> m_conn_params;
    boost::asio::io_context m_ctx; 
    std::unique_ptr<boost::asio::ip::tcp::resolver> m_resolver;          
    std::unique_ptr<boost::asio::ssl::context> m_ssl_ctx;                 
    std::unique_ptr<boost::mysql::tcp_ssl_connection> m_connection;             
    //boost::mysql::statement m_stmt;                      
    //boost::mysql::results m_result;                      
    boost::mysql::diagnostics m_diag;
public:
    SQL_IO(const char * username, const char * password, const char *database);
    ~SQL_IO();       
    void log(std::string text, std::string level);
    void start_connect(std::string hostname);
    void execute_request(const std::string & request);    
    std::unique_ptr<boost::mysql::results> execute_request_with_answer(const std::string & request);

};