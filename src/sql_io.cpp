#include "sql_io.h"

SQL_IO::SQL_IO(const char * username, const char * password, const char *database)
{
    m_ssl_ctx = std::make_unique<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);
    m_connection = std::make_unique<boost::mysql::tcp_ssl_connection>(m_ctx, *m_ssl_ctx);
    m_conn_params = std::make_unique<boost::mysql::handshake_params>(username, password, database);
    m_resolver = std::make_unique<boost::asio::ip::tcp::resolver>(m_ctx.get_executor());
    
    m_connection = std::make_unique<boost::mysql::tcp_ssl_connection>(m_ctx, *m_ssl_ctx);
    sql_logger()->debug("[{}] [{}] SQL_IO constructed", __FILE__, __LINE__);
    //start_connect("172.16.0.1");
}

SQL_IO::~SQL_IO()
{
    if(m_connection)
        m_connection->close();
}

void SQL_IO::log(std::string text, std::string level)
{
    if(level == "debug")
        sql_logger()->debug("[{}], [line {}], {}", __FILE__, __LINE__, text);
    else if(level == "info")
        sql_logger()->info(text);
}

void SQL_IO::start_connect(std::string hostname)
{
    sql_logger()->debug("[{}] [{}] SQL_IO::start_connect - start", __FILE__, __LINE__);
    m_endpoint = m_resolver->resolve(hostname, "3311");
    sql_logger()->debug("[{}] [{}] SQL_IO::async_resolve - end", __FILE__, __LINE__);
    m_connection->connect(*m_endpoint.begin(), *m_conn_params);
    log("succsesfull connect to mysql dtb", "debug");
}

void SQL_IO::execute_request(const std::string & request)
{
    boost::mysql::error_code ec;
    boost::mysql::diagnostics diag;
    std::unique_ptr<boost::mysql::results> result = std::make_unique<boost::mysql::results>();
    m_connection->query(request, *result, ec, diag);
    if (ec){
        web_logger()->error("[SQL_IO::execute_request_with_answer] can't execute request [{}]\n, error message [{}]\n, server.diagnostics [{}]", 
            request, ec.message(), diag.server_message());
    }
}

std::unique_ptr<boost::mysql::results> SQL_IO::execute_request_with_answer(const std::string &request)
{
    web_logger()->debug("SQL_IO::execute_request_with_answer - request [{}]", request);
    std::unique_ptr<boost::mysql::results> result = std::make_unique<boost::mysql::results>();
    boost::mysql::error_code ec;
    boost::mysql::diagnostics diag;
    
    m_connection->query(request, *result, ec, diag);
    if (ec){
        web_logger()->error("[SQL_IO::execute_request_with_answer] can't execute request [{}]\n, error message [{}]\n, server.diagnostics [{}]", 
            request, ec.message(), diag.server_message());
    }
   
    return std::move(result);
}
