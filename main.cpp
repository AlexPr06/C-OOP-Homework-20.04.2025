/*
# 🗂 Проєкт: "Облік проєктів"

## 🎯 Мета:
Програма дозволяє створювати, зберігати, переглядати та призначати проєкти учасникам команд.

---

## 📦 Класи та структура

### 1. Клас `Project`
**🧩 Опис:**
Представляє одиничний проєкт з ключовими властивостями.

**📌 Поля:**
- `string name` — назва проєкту.
- `string description` — короткий опис.
- `string deadline` — строк завершення (рядок).
- `string status` — поточний стан ("У процесі", "Завершено", "Заплановано").

**🛠 Методи:**
- `Project(string n, string d, string dl, string s = "У процесі")` — конструктор.
- `string getName() const` — повертає назву.
- `void print() const` — виводить усю інформацію.

---

### 2. Клас `TeamMember`
**🧩 Опис:**
Учасник команди, який може бути призначений до кількох проєктів.

**📌 Поля:**
- `string name` — ім’я члена команди.
- `string role` — посада або роль.
- `vector<Project*> projects` — вектор призначених проєктів.

**🛠 Методи:**
- `TeamMember(string n, string r)` — конструктор.
- `void assignProject(Project* p)` — додати проєкт до учасника.
- `void print() const` — вивести список призначених проєктів.

---

### 3. Клас `ProjectManager`
**🧩 Опис:**
Керує всіма проєктами в системі.

**📌 Поля:**
- `vector<Project> projects` — список наявних проєктів.

**🛠 Методи:**
- `void addProject(const Project& p)` — додати новий проєкт.
- `void listProjects() const` — вивести всі проєкти.
- `Project* findProject(const string& name)` — знайти проєкт за назвою.
- `void removeProject(const string& name)` *(додатково)* — видалити проєкт зі списку.

---

### 4. Клас `ProjectDatabase` *(опціонально)*

**🧩 Опис:**
Імітує базу даних у пам’яті програми.

**📌 Поля:**
- `vector<Project> storage` — список збережених проєктів.

**🛠 Методи:**
- `void save(const Project& p)` — зберегти новий проєкт.
- `vector<Project> loadAll() const` — повернути всі проєкти зі сховища.

---

### 🛠 Покращення:

- ✅ Клас `Date` — для зберігання дати у вигляді `day`, `month`, `year`.
- ✅ Меню з вибором дій (консольний інтерфейс).
- ✅ Можливість видалення, редагування, пошуку та фільтрації проєктів.
- ✅ Збереження у файл (`.txt`, `.json`, `.csv` — опціонально).
- ✅ Зв’язок між `TeamMember` і `Project` через вказівники (`Project*`).

---

## 📄 Код
Основний код доступний у файлі `main.cpp`.

---
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// === Клас Project ===
class Project {
private:
    string name;
    string description;
    string deadline;
    string status;

public:
    Project(string n, string d, string dl, string s = "У процесі")
        : name(n), description(d), deadline(dl), status(s) {
    }

    string getName() const { return name; }

    void print() const {
        cout << "Назва: " << name << endl;
        cout << "Опис: " << description << endl;
        cout << "Дедлайн: " << deadline << endl;
        cout << "Статус: " << status << endl;
    }
};

// === Клас TeamMember ===
class TeamMember {
private:
    string name;
    string role;
    vector<Project*> projects;

public:
    TeamMember(string n, string r) : name(n), role(r) {}

    void assignProject(Project* p) {
        projects.push_back(p);
    }

    void print() const {
        cout << "\nУчасник: " << name << "\nРоль: " << role << "\nПроєкти:\n";
        if (projects.empty()) {
            cout << "  - Немає призначених проєктів\n";
        }
        else {
            for (auto p : projects) {
                cout << "  - " << p->getName() << "\n";
            }
        }
    }
};

// === Клас ProjectManager ===
class ProjectManager {
private:
    vector<Project> projects;

public:
    void addProject(const Project& p) {
        projects.push_back(p);
    }

    void listProjects() const {
        cout << "\n=== Список усіх проєктів ===\n";
        if (projects.empty()) {
            cout << "Немає проєктів.\n";
            return;
        }
        for (const auto& p : projects) {
            p.print();
            cout << "-------------------------\n";
        }
    }

    Project* findProject(const string& name) {
        for (auto& p : projects) {
            if (p.getName() == name)
                return &p;
        }
        return nullptr;
    }
};

// === Головна функція ===
int main() {
    system("chcp 65001 > nul");
    ProjectManager manager;

    // Створення проєктів
    Project p1("Сайт компанії", "Розробка вебсайту для клієнта", "01.07.2025");
    Project p2("Мобільний застосунок", "Android-додаток для магазину", "15.09.2025", "Заплановано");

    // Додавання проєктів до менеджера
    manager.addProject(p1);
    manager.addProject(p2);

    // Створення учасника команди
    TeamMember member("Іван Петренко", "Розробник");

    // Призначення проєкту учаснику
    Project* found = manager.findProject("Сайт компанії");
    if (found) {
        member.assignProject(found);
    }

    // Виведення інформації
    manager.listProjects();
    member.print();

    return 0;
}

