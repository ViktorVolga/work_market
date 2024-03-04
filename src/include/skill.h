#include <string>
#include <map>
#include <set>

class Skil{
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
    };
    std::map<std::string, int> my_multy_world_skills{
        {"стандартные алгоритмы и структуры данных", 4},
        {"алгоритмы и структуры данных", 4},
        {"английском языке", 6},
        {"Архитектура компьютера", 7},
        {"дисковый ввод-вывод", 7},
        {"сети передачи данных", 8},
        {"протоколы передачи данных", 8}
    };
    std::set<std::string> my_ignoring_worlds{
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
};
