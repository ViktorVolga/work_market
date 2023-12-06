#pragma once 

#include "web_request.h"
#include "json.h"
#include <memory>
#include <queue>

class App
{    
public:
    App();    
    void take_request();
    void get_json();    
};