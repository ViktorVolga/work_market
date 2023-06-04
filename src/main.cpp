#include <iostream>
#include "web_request.h"
#include "logger.h"
#define DEBUG_VERSION 

int main(){
    
    Request request;
    request.add_options_in_request("text=C++");          
    request.set_options();
    request.take_answer();
    request.print_answer();    
    return 0;
}