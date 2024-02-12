#include <nlohmann/json.hpp>
#include <iostream>

class JsonParser
{
    nlohmann::json m_json;
public:
    JsonParser(const std::string &in);
};