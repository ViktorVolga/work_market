#pragma once

#include <string>
#include <set>
#include <filesystem>
#include <boost/lexical_cast.hpp>

#include "vacansy.h"
#include "logger.h"
#include "web_request.h"

class Request;

class VacansySaver{    
public:    
    virtual void resolve_save(std::unique_ptr<Vacansy> & vacansy) = 0;
};

class SaveAsJson : public VacansySaver{
    std::filesystem::path my_path;
    std::set<int> my_already_saved_ids;
public:
    SaveAsJson(std::string path);
    void resolve_save(std::unique_ptr<Vacansy> & vacansy) override;
    bool is_saved(Request * request);
};


static std::shared_ptr<VacansySaver> vacansy_saver_ptr_t;

const std::shared_ptr<VacansySaver> get_vacansy_saver_ptr();