#include "json.h"


JsonParser::JsonParser(const std::string &in)
{
    nlohmann::json j(in);
    std::cout << j << std::endl;
}
