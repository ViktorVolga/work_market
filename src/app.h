#pragma once 

#include "web_request.h"
#include "json.h"

class App
{
   ProfessionRequest my_request{ProfessionRequest()};
public:
    App();
    void take_request();
    void get_json();    
};