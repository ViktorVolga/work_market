#include "vacansy.h"

Vacansy::Vacansy()
{

}

void Vacansy::set_my_id(int id)
{
    my_id = id;
}

int Vacansy::get_my_id()
{
    return my_id;
}

void Vacansy::set_my_name(std::string &name)
{
    my_name = std::move(name);
}

std::string Vacansy::get_my_name()
{
    return my_name;
}

void Vacansy::set_my_country(std::string &country)
{
    my_country = std::move(country);
}

std::string Vacansy::get_my_country()
{
    return my_country;
}
