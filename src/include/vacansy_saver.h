#pragma once

#include <string>
#include <set>
#include <filesystem>
#include <boost/lexical_cast.hpp>

#include "vacansy.h"
#include "logger.h"
#include "web_request.h"
#include "sql_io.h"
#include <unordered_set>

class Request;

class VacansySaver{    
public:    
    virtual void resolve_save(std::unique_ptr<Vacansy> & vacansy) = 0;
    virtual bool is_saved(Request * request) = 0;
    virtual void add_to_saved(int external_id) = 0;
};

class SaveAsJson : public VacansySaver{
    std::filesystem::path my_path;
    std::set<int> my_already_saved_ids;
public:
    SaveAsJson(std::string path);
    void resolve_save(std::unique_ptr<Vacansy> & vacansy) override;
    bool is_saved(Request * request) override;
    std::unique_ptr<Vacansy> read_vacansy(int id);
    void add_to_saved(int external_id) override;
};

struct Countries{
    int m_id {0};
    std::string m_name;    
};

struct Cities{
    int m_id {0};
    std::string m_name;
    int m_country_id {0}; 
    bool m_unknown = false;   
};

struct Company{
    int m_id{0};
    std::string m_name;
    Company(const int id, const std::string & name): m_id(id), m_name(name){};    
};

struct Companies{
    int m_id{0};
    int m_city_id{0};
    int m_company_id{0};
    Companies(const int id, const int city_id, const int company_id): m_id(id), m_city_id(city_id), m_company_id(company_id) {};    
};

struct MinimalVacancy{
    int m_id{0};
    int m_external_id{0};
    std::string m_name;
    std::string m_description;
    bool m_is_actual;
};

struct Vacancies{
    int m_company_id {0};
    int m_vacancy_id {0};
};

struct SalaryDtb{
    int m_id {};
    int m_from {0};
    int m_to {0};
};

struct VacancySalaryDtb{
    int m_id;
    int m_vacancy_id;
    int m_salary_id;
};

struct Requirements{
    int m_id;
    std::string m_aplicant_level;
    std::string m_expirience;
};

struct VacancyRequirements{
    int m_id;
    int m_vacancy_id;
    int m_requirements_id;
};

struct SalaryRequirements{
    int m_id;
    int m_salary_id;
    int m_requirements_id;
};

struct VacancyTables{
    std::unique_ptr <Countries> m_country;
    std::unique_ptr <Cities> m_city;
    std::unique_ptr <Company> m_company;
    std::unique_ptr <Companies> m_companies;
    std::unique_ptr <MinimalVacancy> m_vacancy;
    std::unique_ptr <Vacancies> m_vacancies;
    std::unique_ptr <SalaryDtb> m_salary;
    std::unique_ptr <VacancySalaryDtb> m_vacancy_salary;
    std::unique_ptr <Requirements> m_requirements;
    std::unique_ptr <VacancyRequirements> m_vr;
    std::unique_ptr <SalaryRequirements> m_sr;
};

class SaveInSQL : public VacansySaver{
    std::unique_ptr<SQL_IO> m_sql;
    std::unordered_set<int> m_saved_vacancies;
    std::map<std::string, std::string> m_city_country{
        {"Москва", "Russia"}, {"Санкт-Петербург", "Russia"},
        {"Германия", "Germany"}
    };

    void save_city(const std::string & city, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<Company> get_company_by_name(const std::string & company);
    void prepare_company(const std::string & company, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<Companies> get_companies(int city_id, int company_id);
    void prepare_companies(std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<MinimalVacancy> get_vacancy_by_external_id(int external_id);
    void prepare_vacancy(std::shared_ptr<VacancyTables> vt, int external_id, std::string & name, std::string & description);    
    std::unique_ptr<Vacancies> get_vacancies(int vacancy_id, int company_id);
    void prepare_vacancies(int vacancy_id, int company_id, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<SalaryDtb> get_salary_dtb(int from, int to);
    void prepare_salary(int from, int to, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<VacancySalaryDtb> get_vacancy_salary_dtb(int vacancy_id, int salary_id);
    void prepare_vacancy_salary(int vacancy_id, int salary_id, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<Requirements> get_requirements(std::string & applicant_level, std::string & expirience);
    void prepare_requirements(ApplicantLevel applicant_level, Expirience expirience, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<VacancyRequirements> get_vr(int vacancy_id, int requirements_id);
    void prepare_vr(int vacancy_id, int requirements_id, std::shared_ptr<VacancyTables> vt);
    std::unique_ptr<SalaryRequirements> get_sr(int salary_id, int requirements_id);
    void prepare_sr(int salary_id, int requirements_id, std::shared_ptr<VacancyTables> vt);
public:
    SaveInSQL();
    void resolve_save(std::unique_ptr<Vacansy> & vacansy) override;
    bool is_saved(Request * request) override;
    void add_to_saved(int external_id) override;
};


static std::shared_ptr<VacansySaver> vacansy_saver_ptr_t;

const std::shared_ptr<VacansySaver> get_vacansy_saver_ptr();