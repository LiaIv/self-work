// linked_list.cpp

#include "linked_list.h"
#include <iostream>
#include <algorithm>

// Конструктор
LinkedList::LinkedList(PrimarySortAttribute primaryAttr, SecondarySortAttribute secondaryAttr,
                       SortOrder primaryOrd, SortOrder secondaryOrd)
    : head(nullptr),
      primaryAttribute(primaryAttr),
      secondaryAttribute(secondaryAttr),
      primaryOrder(primaryOrd),
      secondaryOrder(secondaryOrd) {}

// Перемещающий конструктор
LinkedList::LinkedList(LinkedList&& other) noexcept
    : head(std::move(other.head)),
      primaryAttribute(other.primaryAttribute),
      secondaryAttribute(other.secondaryAttribute),
      primaryOrder(other.primaryOrder),
      secondaryOrder(other.secondaryOrder) {}

// Перемещающий оператор присваивания
LinkedList& LinkedList::operator=(LinkedList&& other) noexcept {
    if(this != &other) {
        head = std::move(other.head);
        primaryAttribute = other.primaryAttribute;
        secondaryAttribute = other.secondaryAttribute;
        primaryOrder = other.primaryOrder;
        secondaryOrder = other.secondaryOrder;
    }
    return *this;
}

// Деструктор
LinkedList::~LinkedList() {
    // Умные указатели автоматически освобождают память
}

// Функция сравнения для сортировки
bool LinkedList::compare(const Contact& a, const Contact& b) const {
    // Сравнение по первичному атрибуту
    bool primaryComparison;
    if(primaryAttribute == PrimarySortAttribute::NAME) {
        if(primaryOrder == SortOrder::ASCENDING)
            primaryComparison = a.name < b.name;
        else
            primaryComparison = a.name > b.name;
    }
    else { // CITY
        if(primaryOrder == SortOrder::ASCENDING)
            primaryComparison = a.city < b.city;
        else
            primaryComparison = a.city > b.city;
    }

    if(primaryComparison)
        return true;
    else if(!primaryComparison) {
        // Сравнение по второстепенному атрибуту, если первичные атрибуты равны
        if(secondaryAttribute == SecondarySortAttribute::NAME) {
            if(secondaryOrder == SortOrder::ASCENDING)
                return a.name < b.name;
            else
                return a.name > b.name;
        }
        else { // CITY
            if(secondaryOrder == SortOrder::ASCENDING)
                return a.city < b.city;
            else
                return a.city > b.city;
        }
    }
    return false;
}

// Вставка в список с сортировкой
void LinkedList::insert(const Contact& contact) {
    // Создание нового узла
    std::unique_ptr<ListNode> newNode = std::make_unique<ListNode>(contact);
    
    // Если список пуст или новый элемент должен быть первым
    if(!head || compare(contact, head->contact)) {
        newNode->next = std::move(head);
        head = std::move(newNode);
        return;
    }

    // Поиск позиции для вставки
    ListNode* current = head.get();
    while(current->next && !compare(contact, current->next->contact)) {
        current = current->next.get();
    }

    // Вставка после текущего узла
    newNode->next = std::move(current->next);
    current->next = std::move(newNode);
}

// Вывод списка в порядке сортировки
void LinkedList::printSorted() const {
    if(!head) {
        std::cout << "Линейный список пуст.\n";
        return;
    }
    ListNode* current = head.get();
    while(current) {
        std::cout << "ID: " << current->contact.id << "\n"
                  << "Имя: " << current->contact.name << "\n"
                  << "Номер телефона: " << current->contact.phoneNumber << "\n"
                  << "Город: " << current->contact.city << "\n"
                  << "-----------------------------\n";
        current = current->next.get();
    }
}

// Вывод списка в порядке ввода (не реализовано)
void LinkedList::printInsertionOrder() const {
    // Для сохранения порядка вставки требуется дополнительная структура данных.
    // В текущей реализации список уже отсортирован, поэтому функция не реализована.
    std::cout << "Функция вывода в порядке ввода не реализована.\n";
}

// Поиск по атрибуту
void LinkedList::search(const std::string& key) const {
    bool found = false;
    ListNode* current = head.get();
    while(current) {
        if(primaryAttribute == PrimarySortAttribute::NAME && current->contact.name == key) {
            std::cout << "ID: " << current->contact.id << "\n"
                      << "Имя: " << current->contact.name << "\n"
                      << "Номер телефона: " << current->contact.phoneNumber << "\n"
                      << "Город: " << current->contact.city << "\n"
                      << "-----------------------------\n";
            found = true;
        }
        else if(primaryAttribute == PrimarySortAttribute::CITY && current->contact.city == key) {
            std::cout << "ID: " << current->contact.id << "\n"
                      << "Имя: " << current->contact.name << "\n"
                      << "Номер телефона: " << current->contact.phoneNumber << "\n"
                      << "Город: " << current->contact.city << "\n"
                      << "-----------------------------\n";
            found = true;
        }
        current = current->next.get();
    }
    if(!found) {
        std::cout << "Контакт с " 
                  << (primaryAttribute == PrimarySortAttribute::NAME ? "именем" : "городом") 
                  << " \"" << key << "\" не найден.\n";
    }
}

// Удаление по атрибуту
void LinkedList::remove(const std::string& key) {
    if(!head) {
        std::cout << "Линейный список пуст.\n";
        return;
    }

    // Если первый элемент нужно удалить
    if((primaryAttribute == PrimarySortAttribute::NAME && head->contact.name == key) ||
       (primaryAttribute == PrimarySortAttribute::CITY && head->contact.city == key)) {
        head = std::move(head->next);
        std::cout << "Контакт успешно удален.\n";
        return;
    }

    // Поиск элемента для удаления
    ListNode* current = head.get();
    while(current->next) {
        if((primaryAttribute == PrimarySortAttribute::NAME && current->next->contact.name == key) ||
           (primaryAttribute == PrimarySortAttribute::CITY && current->next->contact.city == key)) {
            current->next = std::move(current->next->next);
            std::cout << "Контакт успешно удален.\n";
            return;
        }
        current = current->next.get();
    }

    std::cout << "Контакт с " 
              << (primaryAttribute == PrimarySortAttribute::NAME ? "именем" : "городом") 
              << " \"" << key << "\" не найден.\n";
}

// Изменение атрибутов сортировки
void LinkedList::changeSortAttributes(PrimarySortAttribute primaryAttr, SecondarySortAttribute secondaryAttr,
                                      SortOrder primaryOrd, SortOrder secondaryOrd) {
    primaryAttribute = primaryAttr;
    secondaryAttribute = secondaryAttr;
    primaryOrder = primaryOrd;
    secondaryOrder = secondaryOrd;

    // Пересортировка списка
    std::vector<Contact> contactList;
    ListNode* current = head.get();
    while(current) {
        contactList.push_back(current->contact);
        current = current->next.get();
    }

    // Очистка списка
    head.reset();

    // Вставка заново с новым порядком сортировки
    for(const auto& contact : contactList) {
        insert(contact);
    }
}

// Сохранение списка в файл
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if(!outFile) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << "\n";
        return;
    }
    ListNode* current = head.get();
    while(current) {
        outFile << current->contact.id << "," 
                << current->contact.name << "," 
                << current->contact.phoneNumber << "," 
                << current->contact.city << "\n";
        current = current->next.get();
    }
    outFile.close();
    std::cout << "Линейный список успешно сохранён в файл " << filename << "\n";
}

// Загрузка списка из файла
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if(!inFile) {
        std::cerr << "Не удалось открыть файл для чтения: " << filename << "\n";
        return;
    }

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

        insert(contact);
    }

    inFile.close();
    std::cout << "Линейный список успешно загружен из файла " << filename << "\n";
}
