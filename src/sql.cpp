#include "sql.h"

void SQLHandler::m_sql_init()
{
    m_ssl_context = std::make_unique<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);
    m_sql_connection = std::make_unique<boost::mysql::tcp_ssl_connection>(m_io_context.get_executor(), *(m_ssl_context.get()));  
}