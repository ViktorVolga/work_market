#include "my_app.h"
#include "include/intro.hpp"

int main(int argc, char * argv[])
{   
    ProgramOptions po(argc, argv);
    po.init();
    
    App my_app = App();
    my_app.run();
     
    return 0;
}
