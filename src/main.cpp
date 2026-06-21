#include "my_app.h"
#include "include/intro.hpp"


int main(int argc, char * argv[])
{   
    //TCPLogWhithOutCompression tcp_log("ip_addr", 3000);
    //ProgramOptions po(argc, argv);
    //po.init();
    
    App my_app = App();
    my_app.run();

   
    /*std::unique_ptr<SQL_IO> m_sql_connect;
    m_sql_connect = std::make_unique<SQL_IO>("root", "12345", "work_market_vacansies"); 
    
    try
    {
        m_sql_connect->start_connect("127.0.0.1");
    }
    catch (const boost::mysql::error_with_diagnostics& err)
    {        
        std::cerr << "Error: " << err.what() << ", error code: " << err.code() << '\n'
                  << "Server diagnostics: " << err.get_diagnostics().server_message() << std::endl;
        return 1;
    }

    m_sql_connect->execute_request("INSERT countries(name) VALUES('Best country in the world')");*/

    return 0;
}
