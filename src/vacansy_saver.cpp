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
