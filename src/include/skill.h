#pragma once

#include <string>
#include <map>
#include <set>
#include <memory>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include "logger.h"

class Skill{
    std::map<std::string, int> my_skills{
        {"linux", 1},
        {"Linux", 1},
        {"Линукс", 1},
        {"Многопоточные", 2},
        {"C", 3},
        {"алгоритмы", 4},
        {"тесты", 5},        
        {"english", 6},         
        {"Оборудование", 7}, 
        {"процессор", 7},
        {"память", 7},
        {"Python", 9},
        {"Питон", 9},
        {"Jira", 10},
        {"SQL", 11},
        {"GitHub", 12},
        {"REST API", 13},
        {"Json", 14},
        {"Flask", 15},
        {"fast API", 16},
        {".NET", 17},
        {"Javascript", 18}
    };
    std::map<std::string, int> my_multy_word_skills{
        {"стандартные алгоритмы и структуры данных", 4},
        {"алгоритмы и структуры данных", 4},
        {"английском языке", 6},
        {"Английский язык", 6},
        {"Архитектура компьютера", 7},
        {"дисковый ввод-вывод", 7},
        {"сети передачи данных", 8},
        {"протоколы передачи данных", 8}
    };
    std::set<std::string> my_ignoring_words{
        "полная", "занятость", "полный", "день", "В", "комапнию разработчика", "систем", "хранения данных", "требуется", "junior", "программиист", 
        "С/С++", "Мы", "разрабатываем", "отечественные", "системы", "хранения", "данных", "Требования", "Законченное", "высшее", "техническое", "образование",
        "Обязательно", "Наличие", "pet", "проектов", "или", "участие", "в", "open", "source", "проектах", "вы", "должны", "любить", "программирование", 
        "Уверенное", "использование", "ОС", "Знания", "по", "программированию", "под", "Linux", "на", "используем", "20", "23", "опыт", "написания", "кода",
        "также", "пригодится", "Знание", "как", "работают", "многопоточные", "приложения", "понимание", "работы", "вызовов", "умение", "применять", "способность", 
        "быстро", "кода", "кода", "кода", "кода", "кода",
        "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода",
        "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода",
        "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода",
        "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода",
        "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода", "кода",
    };
    std::set<std::string> my_unrecognized_strings{

    };
    std::vector<std::string> my_html_garbage{
        "<p>", "</p>", "&quot;", "<em>", "</em>", "<li>", "</li>", "<ol>", "</ol>", "<strong>", "</strong>", "<ul>", "</ul>"
    };

public:
    Skill(){};
    int is_skill(std::string skill_candidat);
    std::map<std::string, int> & get_skills();
    std::map<std::string, int> & get_multy_word_skills();
    std::set<std::string> & get_ignoring_words();
    std::set<std::string> & get_unrecognized_strings();
    std::vector<std::string> & get_garbage();
    void write_to_file();
    void read_skills_from_file();
    void read_mw_skills_from_file();
    void read_my_ignoring_words();
    void read_my_unrecognized_strings();
    void read_my_html_garbage();
    void read_my_dictionaries();
};

typedef std::shared_ptr<Skill> skill_ptr_t;

static skill_ptr_t singletone_skill;

const skill_ptr_t get_skills();
