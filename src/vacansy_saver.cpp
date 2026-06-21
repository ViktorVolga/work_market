#include "vacansy_saver.h"

SaveAsJson::SaveAsJson(std::string path)
{
    web_logger()->debug("[SaveAsJson::SaveAsJson] - start");

    namespace fs = std::filesystem; 

    my_path = path;
    if (!fs::exists(my_path)) {
        web_logger()->debug("[SaveAsJson::SaveAsJson] - passe path [{}] is not exists - creating new folder", path);
        fs::create_directory(path);
    } else {
        web_logger()->debug("[SaveAsJson::SaveAsJson] - path [{}] already exists", path);
    }

    if(fs::is_empty(my_path)){
        web_logger()->debug("[SaveAsJson::SaveAsJson] - path [{}] is empty", path);
    } else {
        web_logger()->debug("[SaveAsJson::SaveAsJson] - creating list of already saved vacancies");
        for (auto const & dir_entry : fs::directory_iterator(my_path)){            
            int vacansy_id = boost::lexical_cast<int>(dir_entry.path().stem().string());
            my_already_saved_ids.insert(vacansy_id);
        }   
    }
    web_logger()->debug("[SaveAsJson::SaveAsJson] - end"); 
}

void SaveAsJson::resolve_save(std::unique_ptr<Vacansy> &vacansy)
{
    int vacansy_id = vacansy->get_my_id();
    if(my_already_saved_ids.count(vacansy_id)){
        web_logger()->info("[SaveAsJson::resolve_save] already has id [{}]", vacansy_id);
    } else {
        web_logger()->info("[SaveAsJson::resolve_save] saving new vacansy. id [{}]", vacansy_id);
        std::string id = boost::lexical_cast<std::string>(vacansy_id);
        std::string path = my_path;
        path.push_back('/');
        path += id;
        web_logger()->info("[SaveAsJson::resolve_save] full path [{}]", path);

        namespace fs = std::filesystem;  
        const fs::path vacansy_path{path};
        if(!fs::exists(path)){
            std::ofstream vacansy_out_stream(path, std::ios::out | std::ios::trunc);
            vacansy_out_stream << *vacansy.get(); 
        }
                     
    }
}

bool SaveAsJson::is_saved(Request *request)
{
    web_logger()->debug("[SaveAsJson::is_saved] - start");
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

std::unique_ptr<Vacansy> SaveAsJson::read_vacansy(int id)
{
    std::unique_ptr<Vacansy> vacansy_from_file = std::make_unique<HHVacansy>();
    std::string vacansy_path = my_path; 
    vacansy_path.push_back('/');
    vacansy_path += boost::lexical_cast<std::string>(id);
    std::ifstream vacansy_in_stream(vacansy_path, std::ios::in);
    vacansy_in_stream >> *vacansy_from_file.get();

    return std::move(vacansy_from_file);
}

void SaveAsJson::add_to_saved(int external_id)
{
    
}

const std::shared_ptr<VacansySaver> get_vacansy_saver_ptr()
{    
    if (vacansy_saver_ptr_t){
        return vacansy_saver_ptr_t;
    } else {
        vacansy_saver_ptr_t = std::make_shared<SaveInSQL>();
        return vacansy_saver_ptr_t;
    }    
}

void SaveInSQL::save_city(const std::string & city, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::save_city - start");

    /*prepare table for countries and cities*/
    vt->m_country = std::make_unique<Countries>();
    vt->m_city = std::make_unique<Cities>();

    /*check if city in known list*/
    if(auto  it = m_city_country.find(city); it != m_city_country.end()){
        web_logger()->debug("SaveInSQL::save_city - have city in map");
        vt->m_country->m_name = it->second;
        web_logger()->debug("SaveInSQL::save_city - country name [{}]", vt->m_country->m_name);
        /*need know country id from table*/
        std::string request = "SELECT * from countries WHERE name = '" + vt->m_country->m_name + "'";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        if(!result->rows().empty()){
            auto row = result->rows();
            auto fields = row[0].as_vector();                      
            vt->m_city->m_country_id = fields.at(0).as_int64();
            vt->m_city->m_name = city;
            web_logger()->debug("SaveInSQL::save_city - country id [{}]", vt->m_country->m_id);
        } else {            
            std::string request = "INSERT countries(name) VALUES('" + vt->m_country->m_name + "')";
            std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        }
        request = "SELECT * from countries WHERE name = '" + vt->m_country->m_name + "'";
        result = m_sql->execute_request_with_answer(request);
        auto row = result->rows();
        auto fields = row[0].as_vector();                      
        vt->m_city->m_country_id = fields.at(0).as_int64();
        vt->m_city->m_name = city;
        web_logger()->debug("SaveInSQL::save_city - country id [{}]", vt->m_country->m_id);
    } else {
        /*unknow cities -> going to unknown cities*/
        vt->m_city->m_unknown = true;
        vt->m_city->m_name = city;
    }   

    /*already prepared  - saving info*/

    if (vt->m_city->m_unknown){
        web_logger()->debug("SaveInSQL::save_city - vt->m_city->m_unknown");
        std::string request = "SELECT * FROM unknown_cities WHERE city = '" + city + "'";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        if(result->rows().empty()){
            request = "INSERT unknown_cities(city) VALUES('" + city + "')";
            result = m_sql->execute_request_with_answer(request);
            web_logger()->debug("SaveInSQL::save_city - city [{}] saved in unknown_cities", city);
        } else {
            web_logger()->debug("SaveInSQL::save_city - unknown city already in dtb");
        }            
    } else {
        web_logger()->debug("SaveInSQL::save_city - !vt->m_city->m_unknown");
        std::string request = "SELECT * FROM cities WHERE name = '" + city + "'";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        if(!result->rows().empty()){
            web_logger()->debug("DTB already has city [{}], dtb return [{}] rows", city, result->rows().size());
            vt->m_city->m_id = result->rows().at(0).at(0).as_int64();
        } else {           
            m_sql->execute_request("INSERT cities(name, country_id) VALUES('" + 
                city + "', " + boost::lexical_cast<std::string> (vt->m_city->m_country_id) + ")");
            web_logger()->debug("add city [{}], country_id [{}]", city, vt->m_city->m_country_id);
            web_logger()->debug("SaveInSQL::save_city - request [{}]", 
                "INSERT cities(name, country_id) VALUES('" + city + "', " + boost::lexical_cast<std::string> (vt->m_city->m_country_id) + ")");
        }
    }    
}

/*
    request company in dtb and return std::unique_ptr or nullptr
*/
std::unique_ptr<Company> SaveInSQL::get_company_by_name(const std::string & company){
    web_logger()->debug("SaveInSQL::get_company_by_name - start");
    /*check - if already has company in dtb*/
    std::string request = "SELECT * FROM company WHERE name = '" + company + "'";
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if(result->rows().empty()){
        /*company epsent in dtb*/
        web_logger()->debug("SaveInSQL::get_company_by_name company [{}], epsent in dtb", company);
        return nullptr;
    } else {
        auto row = result->rows();
        int company_id = row.at(0).at(0).as_int64();
        web_logger()->debug("SaveInSQL::get_company_by_name company [{}], already in dtb with id [{}]", company, company_id);
        return std::make_unique<Company>(company_id, company);
    }
}

void SaveInSQL::prepare_company(const std::string & company, std::shared_ptr<VacancyTables> vt){
    web_logger()->debug("SaveInSQL::prepare_company - start");
    vt->m_company = get_company_by_name(company);

    if(vt->m_company){
        web_logger()->debug("SaveInSQL::prepare_company - company in dtb - nothing here to do");
    } else {
        std::string request = "INSERT company(name) VALUES ('" + company + "')";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        web_logger()->debug("SaveInSQL::prepare_company - company added in dtb");
        vt->m_company = get_company_by_name(company);
    }    
}

std::unique_ptr<Companies> SaveInSQL::get_companies(int city_id, int company_id){
    web_logger()->debug("SaveInSQL::get_companies - start");
    std::string request = "SELECT * FROM companies WHERE city_id = " 
    + boost::lexical_cast<std::string>(city_id) + " AND company_id = " 
    + boost::lexical_cast<std::string>(company_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_companies - company with id [{}], in city with id [{}] - absent", company_id, city_id);
        return nullptr;
    } else {
        web_logger()->debug("SaveInSQL::get_companies - pair company with id [{}], in city with id [{}] - already in dtb", company_id, city_id);
        auto row = result->rows();
        int id = row.at(0).at(0).as_int64();
        return std::make_unique<Companies>(id, city_id, company_id);
    }
}

void SaveInSQL::prepare_companies(std::shared_ptr<VacancyTables> vt){
    web_logger()->debug("SaveInSQL::prepare_companies - start");
    if(vt->m_city->m_unknown){
        web_logger()->error("SaveInSQL::prepare_companies - city is unknown - cant save in table companies");
        return;
    }
        
    vt->m_companies = get_companies(vt->m_city->m_id, vt->m_company->m_id);
    if(vt->m_companies){
        web_logger()->debug("SaveInSQL::prepare_companies - pair company/city already in dtb - noyhing here to do");
    } else {
        std::string request = "INSERT companies(city_id, company_id) VALUES (" + 
        boost::lexical_cast<std::string>(vt->m_city->m_id) + ", " + 
        boost::lexical_cast<std::string>(vt->m_company->m_id) + ")";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_companies = get_companies(vt->m_city->m_id, vt->m_company->m_id);
    }
}

std::unique_ptr<MinimalVacancy> SaveInSQL::get_vacancy_by_external_id(int external_id){
    web_logger()->debug("SaveInSQL::get_vacancy_by_external_id - start");
    std::string request = "SELECT * FROM vacancy WHERE external_id = " 
    + boost::lexical_cast<std::string>(external_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }

    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::et_vacancy_by_external_id - vacancy with external_id [{}] - absent", external_id);
        return nullptr;
    } else {
        std::unique_ptr<MinimalVacancy> vacancy = std::make_unique<MinimalVacancy>();
        vacancy->m_id = result->rows().at(0).at(0).as_int64();
        vacancy->m_external_id = result->rows().at(0).at(1).as_int64();
        vacancy->m_name = result->rows().at(0).at(2).as_string();
        vacancy->m_description = result->rows().at(0).at(3).as_string();
        if(result->rows().at(0).at(4).as_int64())
            vacancy->m_is_actual = true;
        else
            vacancy->m_is_actual = false; 
        return std::move(vacancy);
    }
}

std::unique_ptr<Vacancies> SaveInSQL::get_vacancies(int vacancy_id, int company_id)
{
    web_logger()->debug("SaveInSQL::get_vacancies - start");
    std::string request = "SELECT * FROM vacancies WHERE vacancy_id = " 
    + boost::lexical_cast<std::string>(vacancy_id) + " AND company_id = "
    + boost::lexical_cast<std::string>(company_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_vacancies - record with vacancy_id [{}] and company_id [{}] is absent in dtb",
        vacancy_id, company_id);
        return nullptr;
    } else {
        std::unique_ptr<Vacancies> vacancies = std::make_unique<Vacancies>();
        vacancies->m_vacancy_id = result->rows().at(0).at(1).as_int64();
        vacancies->m_company_id = result->rows().at(0).at(2).as_int64();
        return std::move(vacancies);
    }    
}

void SaveInSQL::prepare_vacancies(int vacancy_id, int company_id, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_vacancies - start");
    vt->m_vacancies = get_vacancies(vt->m_vacancy->m_id, vt->m_company->m_id);
    if (vt->m_vacancies){
        web_logger()->debug("SaveInSQL::prepare_vacancy - vacancies already in dtb - noyhing here to do");
    } else {
        std::string request = "INSERT vacancies(vacancy_id, company_id) VALUES (" 
        + boost::lexical_cast<std::string>(vt->m_vacancy->m_id) + ", "
        + boost::lexical_cast<std::string>(vt->m_company->m_id) + ")";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_vacancies = get_vacancies(vt->m_vacancy->m_id, vt->m_company->m_id);
    }
}

std::unique_ptr<SalaryDtb> SaveInSQL::get_salary_dtb(int from, int to)
{
    web_logger()->debug("SaveInSQL::get_salary_dtb - start");
    std::string request = "SELECT * FROM salary WHERE _from = " 
    + boost::lexical_cast<std::string>(from) + " AND _to = "
    + boost::lexical_cast<std::string>(to);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        web_logger()->error("can't get salary from dtb");
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_salary_dtb - record with salary from [{}], to [{}] is absent in dtb",
        from, to);
        return nullptr;
    } else {
        std::unique_ptr<SalaryDtb> salary = std::make_unique<SalaryDtb>();
        salary->m_id = result->rows().at(0).at(0).as_int64();
        salary->m_from = result->rows().at(0).at(1).as_int64();
        salary->m_to = result->rows().at(0).at(2).as_int64();
        return std::move(salary);
    }   
}

void SaveInSQL::prepare_salary(int from, int to, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_salary - start");
    vt->m_salary = get_salary_dtb(from, to);
    if(vt->m_salary){
        web_logger()->debug("SaveInSQL::prepare_salary - salary already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT salary(_from, _to) VALUES (" + 
        boost::lexical_cast<std::string>(from) + ", " + 
        boost::lexical_cast<std::string>(to) + ")";
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_salary = get_salary_dtb(from, to);
        if (vt->m_salary == nullptr)
            web_logger()->error("aveInSQL::prepare_salary can't save salary from [{}], to [{}] is absent in dtb",
                from, to);

    }
}

std::unique_ptr<VacancySalaryDtb> SaveInSQL::get_vacancy_salary_dtb(int vacancy_id, int salary_id)
{
    web_logger()->debug("SaveInSQL::get_vacancy_salary_dtb - start");
    std::string request = "SELECT * FROM vacancy_salary WHERE vacancy_id = " 
    + boost::lexical_cast<std::string>(vacancy_id) + " AND salary_id = "
    + boost::lexical_cast<std::string>(salary_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("get_vacancy_salary_dtb - record with vacancy_id [{}], salary_id [{}] is absent in dtb",
        vacancy_id, salary_id);
        return nullptr;
    } else {
        std::unique_ptr<VacancySalaryDtb> vs = std::make_unique<VacancySalaryDtb>();
        vs->m_id = result->rows().at(0).at(0).as_int64();
        vs->m_vacancy_id = result->rows().at(0).at(1).as_int64();
        vs->m_salary_id = result->rows().at(0).at(2).as_int64();
        return std::move(vs);
    }   
}

void SaveInSQL::prepare_vacancy_salary(int vacancy_id, int salary_id, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_vacancy_salary - start");
    vt->m_vacancy_salary = get_vacancy_salary_dtb(vacancy_id, salary_id);
    if(vt->m_vacancy_salary){
        web_logger()->debug("SaveInSQL::prepare_vacancy_salary - vacancy_salary already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT vacancy_salary(vacancy_id, salary_id) VALUES (" + 
        boost::lexical_cast<std::string>(vacancy_id) + ", " + 
        boost::lexical_cast<std::string>(salary_id) + ")";       
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_vacancy_salary = get_vacancy_salary_dtb(vacancy_id, salary_id);
    }
}

std::unique_ptr<Requirements> SaveInSQL::get_requirements(std::string &applicant_level, std::string &expirience)
{
    web_logger()->debug("SaveInSQL::get_requirements - start");
    std::string request = "SELECT * FROM requirements WHERE applicant_level = '" 
    + applicant_level + "' AND expirience = '"
    + expirience + "'";
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_requirements - record with applicant_level [{}], with expirience [{}] is absent in dtb",
        applicant_level, expirience);
        return nullptr;
    } else {
        std::unique_ptr<Requirements> req = std::make_unique<Requirements>();
        req->m_id = result->rows().at(0).at(0).as_int64();
        req->m_aplicant_level = result->rows().at(0).at(1).as_string();
        req->m_expirience = result->rows().at(0).at(2).as_string();
        return std::move(req);
    }   
}

void SaveInSQL::prepare_requirements(ApplicantLevel applicant_level, Expirience expirience, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_requirements - start");
    std::string s_applicant_level;
    std::string s_expirience;
    if (applicant_level == ApplicantLevel::june)
        s_applicant_level = "june";
    else if(applicant_level == ApplicantLevel::midle)
        s_applicant_level = "midle";
    else if(applicant_level == ApplicantLevel::senior)
        s_applicant_level = "senior";
    else
        s_applicant_level = "unknown";
    switch (expirience){
        case Expirience::no_expirince :
            s_expirience = "no_expirince";
            break;
        case Expirience::one_three_year :
            s_expirience = "one_three_year";
            break;
        case Expirience::more_three_year:
            s_expirience = "more_three_year";
            break;
        default :
            s_expirience = "unknown";
            break;
    } 

    vt->m_requirements = get_requirements(s_applicant_level, s_expirience);
    if(vt->m_requirements){
        web_logger()->debug("SaveInSQL::prepare_requirements - requirements already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT requirements(applicant_level, expirience) VALUES ('" + 
        s_applicant_level + "', '" + s_expirience + "')";       
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_requirements = get_requirements(s_applicant_level, s_expirience);
    }
}

std::unique_ptr<VacancyRequirements> SaveInSQL::get_vr(int vacancy_id, int requirements_id)
{
    web_logger()->debug("SaveInSQL::get_vr - start");
    std::string request = "SELECT * FROM vacancy_requirements WHERE vacancy_id = " 
    + boost::lexical_cast<std::string>(vacancy_id) + " AND requirements_id = "
    + boost::lexical_cast<std::string>(requirements_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_vr - record with vacancy_id [{}], requirements_id [{}] is absent in dtb",
        vacancy_id, requirements_id);
        return nullptr;
    } else {
        std::unique_ptr<VacancyRequirements> vr = std::make_unique<VacancyRequirements>();
        vr->m_id = result->rows().at(0).at(0).as_int64();
        vr->m_vacancy_id = result->rows().at(0).at(1).as_int64();
        vr->m_requirements_id = result->rows().at(0).at(2).as_int64();
        return std::move(vr);
    }
}

void SaveInSQL::prepare_vr(int vacancy_id, int requirements_id, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_vr - start");
    vt->m_vr = get_vr(vacancy_id, requirements_id);
    if(vt->m_vr){
        web_logger()->debug("SaveInSQL::prepare_vr - pair vacancy/requirements already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT vacancy_requirements(vacancy_id, requirements_id) VALUES (" + 
        boost::lexical_cast<std::string>(vacancy_id) + ", " + boost::lexical_cast<std::string>(requirements_id)  + ")";       
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_vr = get_vr(vacancy_id, requirements_id);
        web_logger()->debug("SaveInSQL::prepare_vr - pair vacancy_id [{}] requirements_id [{}] added in dtb", vacancy_id, requirements_id);
    }
}

std::unique_ptr<SalaryRequirements> SaveInSQL::get_sr(int salary_id, int requirements_id)
{
    web_logger()->debug("SaveInSQL::get_sr - start");
    std::string request = "SELECT * FROM salary_requirements WHERE salary_id = " 
    + boost::lexical_cast<std::string>(salary_id) + " AND requirements_id = "
    + boost::lexical_cast<std::string>(requirements_id);
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
    if (!result){
        return nullptr;
    }
    if(result->rows().empty()){
        web_logger()->debug("SaveInSQL::get_sr - record with salary_id [{}], requirements_id [{}] is absent in dtb",
        salary_id, requirements_id);
        return nullptr;
    } else {
        std::unique_ptr<SalaryRequirements> sr = std::make_unique<SalaryRequirements>();
        sr->m_id = result->rows().at(0).at(0).as_int64();
        sr->m_salary_id = result->rows().at(0).at(1).as_int64();
        sr->m_requirements_id = result->rows().at(0).at(2).as_int64();
        return std::move(sr);
    }
}

void SaveInSQL::prepare_sr(int salary_id, int requirements_id, std::shared_ptr<VacancyTables> vt)
{
    web_logger()->debug("SaveInSQL::prepare_sr - start");
    vt->m_sr = get_sr(salary_id, requirements_id);
    if(vt->m_sr){
        web_logger()->debug("SaveInSQL::prepare_sr - pair salary/requirements already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT salary_requirements(salary_id, requirements_id) VALUES (" + 
        boost::lexical_cast<std::string>(salary_id) + ", " + boost::lexical_cast<std::string>(requirements_id)  + ")";       
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_sr = get_sr(salary_id, requirements_id);
        web_logger()->debug("SaveInSQL::prepare_sr - pair salary_id [{}] requirements_id [{}] added in dtb", salary_id, requirements_id);
    }
}

void SaveInSQL::prepare_vacancy(std::shared_ptr<VacancyTables> vt, int external_id, std::string & name, std::string & description){
    web_logger()->debug("SaveInSQL::prepare_vacancy - start");
    vt->m_vacancy = get_vacancy_by_external_id(external_id);
    if(vt->m_vacancy){
        web_logger()->debug("SaveInSQL::prepare_vacancy - vacancy already in dtb - noyhing here to do");
    } else {        
        std::string request = "INSERT vacancy(external_id, name, description, is_actual) VALUES (" + 
        boost::lexical_cast<std::string>(external_id) + ", '" + 
        name + "', '" + description + "', TRUE)";       
        std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer(request);
        vt->m_vacancy = get_vacancy_by_external_id(external_id);
        if (!vt->m_vacancy)
            web_logger()->error("SaveInSQL::prepare_vacancy - error with saving vacancy external_id [{}], name [{}]",
                external_id, name);
    }
}

SaveInSQL::SaveInSQL()
{
    /*todo later - get values for connection from json*/
    m_sql = std::make_unique<SQL_IO>("root", "12345", "work_market_vacansies");
    try
    {
        m_sql->start_connect("127.0.0.1");
    }
    catch (const boost::mysql::error_with_diagnostics& err)
    {
        web_logger()->error("[{}]", err.what());
    }
    std::unique_ptr<boost::mysql::results> result = m_sql->execute_request_with_answer("SELECT * FROM vacancy");
    for (auto row : result->rows()){
        m_saved_vacancies.emplace(row.at(1).as_int64());  
    }

}

void SaveInSQL::resolve_save(std::unique_ptr<Vacansy> &vacansy)
{
    std::shared_ptr <VacancyTables> vacansy_tables = std::make_shared<VacancyTables>();
    save_city(vacansy->get_my_city(), vacansy_tables); 
    prepare_company(vacansy->get_my_company(), vacansy_tables);
    prepare_companies(vacansy_tables);
    prepare_vacancy(vacansy_tables, vacansy->get_my_id(), vacansy->get_my_name(), vacansy->get_my_descripton());
    prepare_vacancies(vacansy_tables->m_company->m_id ,vacansy_tables->m_company->m_id, vacansy_tables);
    prepare_salary(vacansy->get_my_rub_salary_from(), vacansy->get_my_rub_salary_to(), vacansy_tables);
    prepare_vacancy_salary(vacansy_tables->m_vacancy->m_id, vacansy_tables->m_salary->m_id, vacansy_tables);
    prepare_requirements(vacansy->get_my_level(), vacansy->get_my_expirience(), vacansy_tables);
    prepare_vr(vacansy_tables->m_vacancy->m_id, vacansy_tables->m_requirements->m_id, vacansy_tables);
    if(vacansy_tables->m_salary && vacansy_tables->m_requirements)
        prepare_sr(vacansy_tables->m_salary->m_id, vacansy_tables->m_requirements->m_id, vacansy_tables);
    else{
        if(!vacansy_tables->m_salary)
            web_logger()->error("vacansy_tables->m_salary is null");
        else
            web_logger()->error("vacansy_tables->m_requirements is null");
    }
        
}

bool SaveInSQL::is_saved(Request * request)
{    
    web_logger()->debug("[SaveInSQL::is_saved] - start");
    if(!request)
        return false;

    auto req_type = request->get_request_type();
    switch (req_type){
        case request_type_t::HHVacansyRequest :
            HHVacansyRequest * vacansy_request = dynamic_cast<HHVacansyRequest*>(request);
            if(vacansy_request){
                auto id = vacansy_request->get_id();
                auto founded_it = m_saved_vacancies.find(id);
                if(founded_it == m_saved_vacancies.end())
                    return false;                    
                else
                    return true;
            } else {
                return false;
            }
       
    }
    return false;
}

void SaveInSQL::add_to_saved(int external_id)
{
    m_saved_vacancies.emplace(external_id);
}
