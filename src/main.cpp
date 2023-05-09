#include <iostream>
#include "web_request.h"

int main()
{
    std::cout << "hello from conteiner" << std::endl;
    Request request;
    //request.add_options_in_request("c++");          
    request.set_options();
    request.take_answer();
    request.print_answer();
    return 0;
}