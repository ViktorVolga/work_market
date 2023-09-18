#include "sql.h"

SQLHandler::SQLHandler()
{
    get_driver();
    set_properties(ConnectOptions::host_name, "tcp://127.0.0.1");
    set_properties(ConnectOptions::port, "3306");
    set_properties(ConnectOptions::user_name, "root");
    set_properties(ConnectOptions::password, "root");
    connect();
}

SQLHandler::~SQLHandler()
{
    if(m_con)
        delete m_con;
}

uint8_t SQLHandler::get_driver()
{
    m_driver = get_driver_instance();
    if(!m_driver)
    {
        std::cout << "cant't take sql.driver" << std::endl;
        return 1;
    }
    else
    {
        std::cout <<  "sql.driver got - ok" << std::endl;
        return 0;
    }    
}

void SQLHandler::set_properties(const ConnectOptions &option, const std::string &value)
{
    switch (option)
    {
        case ConnectOptions::host_name :
            m_connection_properties["host_name"] = value;
            break;
        case ConnectOptions::password :
            m_connection_properties["password"] = value;
            break;
        case ConnectOptions::port :
            m_connection_properties["port"] = std::stoi(value);
            break;
        case ConnectOptions::user_name :
            m_connection_properties["username"] = value;
            break;            
    }
}

void SQLHandler::connect()
{   
    try
    {
        m_con = m_driver->connect(m_connection_properties);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }    
    
    if(m_con->isValid())
    {
        std::cout << "connection - ok" << std::endl;
    }
    else
    {
        std::cout << "can't connect to database" << std::endl;
    }
}
