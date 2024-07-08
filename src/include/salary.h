#pragma once

#include <string>
#include <memory>

class Salary
{
    int from {};
    int to {};
public:
    Salary(const int from, const int to);
    std::string get_from();
    std::string get_to();
    int & get_int_from();
    int & get_int_to();
};

typedef std::unique_ptr<Salary> salary_ptr_t;