// contact.cpp

#include "contact.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>

// Инициализация глобального счётчика
int global_id_counter = 1;

// Ввод данных контактов с валидацией
void inputContacts(std::vector<Contact>& contacts) {
    int numContacts;
    std::cout << "Введите количество контактов: ";
    while(!(std::cin >> numContacts) || numContacts < 0) {
        std::cout << "Некорректный ввод. Введите положительное число: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера

    for(int i = 0; i < numContacts; ++i) {
        Contact contact;
        contact.id = global_id_counter++; // Присвоение уникального ID

        // Ввод имени с проверкой
        while(true) {
            std::cout << "Введите имя контакта: ";
            std::getline(std::cin, contact.name);
            if(validateName(contact.name))
                break;
            else
                std::cout << "Имя не может быть пустым. Пожалуйста, попробуйте снова.\n";
        }

        // Ввод номера телефона с проверкой
        while(true) {
            std::cout << "Введите номер телефона (только цифры, 7-15 символов): ";
            std::getline(std::cin, contact.phoneNumber);
            if(validatePhoneNumber(contact.phoneNumber))
                break;
            else
                std::cout << "Некорректный формат номера телефона. Пожалуйста, попробуйте снова.\n";
        }

        // Ввод города с проверкой
        while(true) {
            std::cout << "Введите город: ";
            std::getline(std::cin, contact.city);
            if(validateCity(contact.city))
                break;
            else
                std::cout << "Город не может быть пустым. Пожалуйста, попробуйте снова.\n";
        }

        contacts.push_back(contact);
    }
}

// Построение индекс-массивов
void IndexArray::buildIndices(const std::vector<Contact>& contacts) {
    nameIndexAsc.clear();
    nameIndexDesc.clear();
    cityIndexAsc.clear();
    cityIndexDesc.clear();

    for(const auto& contact : contacts) {
        Index idx;
        idx.key = contact.name;
        idx.recordNumber = contact.id;
        nameIndexAsc.push_back(idx);
        nameIndexDesc.push_back(idx);

        idx.key = contact.city;
        cityIndexAsc.push_back(idx);
        cityIndexDesc.push_back(idx);
    }
}

// Сортировка индекс-массивов
void IndexArray::sortIndices() {
    // Сортировка по имени по возрастанию
    std::sort(nameIndexAsc.begin(), nameIndexAsc.end(),
              [](const Index& a, const Index& b) { return a.key < b.key; });

    // Сортировка по имени по убыванию
    std::sort(nameIndexDesc.begin(), nameIndexDesc.end(),
              [](const Index& a, const Index& b) { return a.key > b.key; });

    // Сортировка по городу по возрастанию
    std::sort(cityIndexAsc.begin(), cityIndexAsc.end(),
              [](const Index& a, const Index& b) { return a.key < b.key; });

    // Сортировка по городу по убыванию
    std::sort(cityIndexDesc.begin(), cityIndexDesc.end(),
              [](const Index& a, const Index& b) { return a.key > b.key; });
}

// Вывод всех контактов
void printContacts(const std::vector<Contact>& contacts) {
    std::cout << "\nСписок контактов:\n";
    for(const auto& contact : contacts) {
        std::cout << "ID: " << contact.id << "\n"
                  << "Имя: " << contact.name << "\n"
                  << "Номер телефона: " << contact.phoneNumber << "\n"
                  << "Город: " << contact.city << "\n"
                  << "-----------------------------\n";
    }
}

// Вывод отсортированных контактов по имени
void printSortedByName(const std::vector<Contact>& contacts, const std::vector<Index>& nameIndex) {
    for(const auto& idx : nameIndex) {
        // Поиск контакта по ID
        auto it = std::find_if(contacts.begin(), contacts.end(),
                               [&](const Contact& c) { return c.id == idx.recordNumber; });
        if(it != contacts.end()) {
            std::cout << "ID: " << it->id << "\n"
                      << "Имя: " << it->name << "\n"
                      << "Номер телефона: " << it->phoneNumber << "\n"
                      << "Город: " << it->city << "\n"
                      << "-----------------------------\n";
        }
        else {
            std::cerr << "Ошибка: Контакт с ID " << idx.recordNumber << " не найден.\n";
        }
    }
}

// Вывод отсортированных контактов по городу
void printSortedByCity(const std::vector<Contact>& contacts, const std::vector<Index>& cityIndex) {
    for(const auto& idx : cityIndex) {
        // Поиск контакта по ID
        auto it = std::find_if(contacts.begin(), contacts.end(),
                               [&](const Contact& c) { return c.id == idx.recordNumber; });
        if(it != contacts.end()) {
            std::cout << "ID: " << it->id << "\n"
                      << "Имя: " << it->name << "\n"
                      << "Номер телефона: " << it->phoneNumber << "\n"
                      << "Город: " << it->city << "\n"
                      << "-----------------------------\n";
        }
        else {
            std::cerr << "Ошибка: Контакт с ID " << idx.recordNumber << " не найден.\n";
        }
    }
}

// Итеративный бинарный поиск
std::vector<int> binarySearchIterative(const std::vector<Index>& indexArray, const std::string& key) {
    std::vector<int> result;
    int left = 0;
    int right = indexArray.size() - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(indexArray[mid].key == key) {
            // Найти все записи с этим ключом
            // Ищем левую границу
            int start = mid;
            while(start > 0 && indexArray[start - 1].key == key) start--;
            // Ищем правую границу
            int end = mid;
            while(end < indexArray.size() - 1 && indexArray[end + 1].key == key) end++;
            // Собираем все recordNumbers
            for(int i = start; i <= end; ++i) {
                result.push_back(indexArray[i].recordNumber);
            }
            break;
        }
        else if(indexArray[mid].key < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return result;
}

// Рекурсивный бинарный поиск
std::vector<int> binarySearchRecursive(const std::vector<Index>& indexArray, const std::string& key, int left, int right) {
    std::vector<int> result;
    if(left > right) return result;

    int mid = left + (right - left) / 2;
    if(indexArray[mid].key == key) {
        // Найти все записи с этим ключом
        // Ищем левую границу
        int start = mid;
        while(start > 0 && indexArray[start - 1].key == key) start--;
        // Ищем правую границу
        int end = mid;
        while(end < indexArray.size() - 1 && indexArray[end + 1].key == key) end++;
        // Собираем все recordNumbers
        for(int i = start; i <= end; ++i) {
            result.push_back(indexArray[i].recordNumber);
        }
    }
    else if(indexArray[mid].key < key) {
        std::vector<int> leftResult = binarySearchRecursive(indexArray, key, mid + 1, right);
        result.insert(result.end(), leftResult.begin(), leftResult.end());
    }
    else {
        std::vector<int> rightResult = binarySearchRecursive(indexArray, key, left, mid - 1);
        result.insert(result.end(), rightResult.begin(), rightResult.end());
    }
    return result;
}

// Редактирование контакта
void editContact(std::vector<Contact>& contacts, IndexArray& indices) {
    std::string key;
    std::cout << "Введите имя контакта для редактирования: ";
    std::getline(std::cin, key);

    bool found = false;
    for(auto& contact : contacts) {
        if(contact.name == key) {
            found = true;
            std::cout << "Введите новое имя контакта (оставьте пустым, чтобы оставить без изменений): ";
            std::string newName;
            std::getline(std::cin, newName);
            if(!newName.empty())
                contact.name = newName;

            std::cout << "Введите новый номер телефона (оставьте пустым, чтобы оставить без изменений): ";
            std::string newPhone;
            std::getline(std::cin, newPhone);
            if(!newPhone.empty()) {
                if(validatePhoneNumber(newPhone))
                    contact.phoneNumber = newPhone;
                else
                    std::cout << "Некорректный формат номера телефона. Оставлено прежнее значение.\n";
            }

            std::cout << "Введите новый город (оставьте пустым, чтобы оставить без изменений): ";
            std::string newCity;
            std::getline(std::cin, newCity);
            if(!newCity.empty())
                contact.city = newCity;

            // Перестроение индекс-массивов
            indices.buildIndices(contacts);
            indices.sortIndices();

            std::cout << "Контакт успешно обновлен.\n";
            break; // Предполагается уникальность имени. Если нет, удалите этот break.
        }
    }
    if(!found) {
        std::cout << "Контакт с именем \"" << key << "\" не найден.\n";
    }
}

// Удаление контакта
void deleteContact(std::vector<Contact>& contacts, IndexArray& indices) {
    std::string key;
    std::cout << "Введите имя контакта для удаления: ";
    std::getline(std::cin, key);

    auto it = std::remove_if(contacts.begin(), contacts.end(),
                             [&](const Contact& c) { return c.name == key; });

    if(it != contacts.end()) {
        contacts.erase(it, contacts.end());
        // Перестроение индекс-массивов
        indices.buildIndices(contacts);
        indices.sortIndices();
        std::cout << "Контакт успешно удален.\n";
    }
    else {
        std::cout << "Контакт с именем \"" << key << "\" не найден.\n";
    }
}

// Проверка на пустое имя
bool validateName(const std::string& name) {
    return !name.empty();
}

// Проверка на пустой город
bool validateCity(const std::string& city) {
    return !city.empty();
}

// Проверка формата номера телефона
bool validatePhoneNumber(const std::string& phoneNumber) {
    if(phoneNumber.length() < 7 || phoneNumber.length() > 15)
        return false;
    for(char c : phoneNumber) {
        if(!std::isdigit(c))
            return false;
    }
    return true;
}

// Сохранение контактов в файл
void saveContactsToFile(const std::vector<Contact>& contacts, const std::string& filename) {
    std::ofstream outFile(filename);
    if(!outFile) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << "\n";
        return;
    }
    for(const auto& contact : contacts) {
        outFile << contact.id << "," << contact.name << "," << contact.phoneNumber << "," << contact.city << "\n";
    }
    outFile.close();
    std::cout << "Контакты успешно сохранены в файл " << filename << "\n";
}

// Загрузка контактов из файла
void loadContactsFromFile(std::vector<Contact>& contacts, const std::string& filename) {
    std::ifstream inFile(filename);
    if(!inFile) {
        std::cerr << "Не удалось открыть файл для чтения: " << filename << "\n";
        return;
    }
    contacts.clear();
    std::string line;
    while(std::getline(inFile, line)) {
        Contact contact;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if(pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
            std::cerr << "Некорректный формат строки: " << line << "\n";
            continue;
        }

        contact.id = std::stoi(line.substr(0, pos1));
        contact.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        contact.phoneNumber = line.substr(pos2 + 1, pos3 - pos2 - 1);
        contact.city = line.substr(pos3 + 1);

        // Обновление глобального счётчика, если необходимо
        if(contact.id >= global_id_counter)
            global_id_counter = contact.id + 1;

        contacts.push_back(contact);
    }
    inFile.close();
    std::cout << "Контакты успешно загружены из файла " << filename << "\n";
}
