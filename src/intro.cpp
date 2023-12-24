#include "include/intro.hpp"

ProgramOptions::ProgramOptions(int argc, char * argv[])
{    
    /*create description for app*/
    my_description = std::make_unique<opt::options_description>("All options");

    /*add some options*/
    my_description->add_options()
        ("user", opt::value<std::string>(), "username")
        ("pass", opt::value<std::string>(), "password")
        ("help", "produce help message")
    ;

    /*parse and save args from command line*/
    try
    {
        opt::store(opt::parse_command_line(argc, argv, *my_description.get()), my_variables);
    }
    catch(const opt::unknown_option & e)
    {
        std::cout << *my_description.get() << std::endl;
    }

}

int ProgramOptions::init()
{
    if(my_variables.count("help"))
    {
        std::cout << *my_description.get() << std::endl;
        return 1;
    }
    return 0;
}