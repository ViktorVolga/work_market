#include "vacansy_saver.h"

SaveAsJson::SaveAsJson(std::string path)
{
    web_logger()->info("[SaveAsJson::SaveAsJson] - start");

    namespace fs = std::filesystem; 

    my_path = path;
    if (!fs::exists(my_path)) {
        web_logger()->info("[SaveAsJson::SaveAsJson] - passe path [{}] is not exists - creating new folder", path);
        fs::create_directory(path);
    } else {
        web_logger()->info("[SaveAsJson::SaveAsJson] - path [{}] already exists", path);
    }

    if(fs::is_empty(my_path)){
        web_logger()->info("[SaveAsJson::SaveAsJson] - path [{}] is empty", path);
    } else {
        web_logger()->info("[SaveAsJson::SaveAsJson] - creating list of already saved vacancies");
        for (auto const & dir_entry : fs::directory_iterator(my_path)){            
            int vacansy_id = boost::lexical_cast<int>(dir_entry.path().stem().string());
            my_already_saved_ids.insert(vacansy_id);
        }   
    }
    web_logger()->info("[SaveAsJson::SaveAsJson] - end"); 
}

void SaveAsJson::resolve_save(std::unique_ptr<Vacansy> &vacansy)
{
    int vacansy_id = vacansy->get_my_id();
    if(my_already_saved_ids.count(vacansy_id)){
        web_logger()->info("[SaveAsJson::resolve_save] salready has id [{}]", vacansy_id);
    } else {
        web_logger()->info("[SaveAsJson::resolve_save] saving new vacansy. id [{}]", vacansy_id);
        std::string id = boost::lexical_cast<std::string>(vacansy_id);
        std::string path = my_path;
        path.push_back('/');
        path.assign(id.begin(), id.end());
        web_logger()->info("[SaveAsJson::resolve_save] full path [{}]", path);
                
    }
}

bool SaveAsJson::is_saved(Request *request)
{
    web_logger()->info("[SaveAsJson::is_saved] - start");
    if(!request)
        return false;

    auto req_type = request->get_request_type();
    switch (req_type){
        case request_type_t::HHVacansyRequest :
            HHVacansyRequest * vacansy_request = dynamic_cast<HHVacansyRequest*>(request);
            if(vacansy_request){
                auto id = vacansy_request->get_id();
                auto founded_it = my_already_saved_ids.find(id);
                if(founded_it == my_already_saved_ids.end())
                    return false;                    
                else
                    return true;
            } else {
                return false;
            }
       
    }
    return false;
}

const std::shared_ptr<VacansySaver> get_vacansy_saver_ptr()
{
    if (vacansy_saver_ptr_t){
        return vacansy_saver_ptr_t;
    } else {
        return std::make_shared<SaveAsJson>("/home/volga/work_market");
    }    
}
