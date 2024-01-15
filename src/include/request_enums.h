#pragma once 

enum class vacansy_parameters{
    specialization,
    per_page,
    text,
    area,
    page,
};

typedef enum class Specializations{
    cpp,
    python,
} specializations_t;

typedef enum class RequestType{
    HHProfRequest,
    HHProfRequestPage,
} request_type_t;