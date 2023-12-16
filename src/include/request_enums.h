#pragma once 

enum class vacansy_parameters{
    specialization,
    per_page,
    text,
    area,
};

typedef enum class Specializations{
    cpp,
    python,
} specializations_t;

typedef enum class RequestType{
    HHProfRequest,
} request_type_t;