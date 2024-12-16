// main.cpp

#include "contact.h"
#include "binary_tree.h" // Подключение заголовочного файла бинарного дерева
#include "linked_list.h" // Подключение заголовочного файла линейного списка
#include <vector>
#include <iostream>
#include <limits>

/**
 * @brief Сохраняет контакты в файл.
 * @param contacts Вектор контактов.
 * @param filename Имя файла для сохранения.
 */
void saveContactsToFile(const std::vector<Contact>& contacts, const std::string& filename);

/**
 * @brief Загружает контакты из файла.
 * @param contacts Вектор контактов для загрузки.
 * @param filename Имя файла для загрузки.
 */
void loadContactsFromFile(std::vector<Contact>& contacts, const std::string& filename);

/**
 * @brief Выводит контакты по заданным индексам.
 * @param contacts Вектор контактов.
 * @param indexIndex Вектор индексов.
 */
void printSortedByName(const std::vector<Contact>& contacts, const std::vector<Index>& nameIndex);

/**
 * @brief Выводит контакты по заданным индексам.
 * @param contacts Вектор контактов.
 * @param cityIndex Вектор индексов.
 */
void printSortedByCity(const std::vector<Contact>& contacts, const std::vector<Index>& cityIndex);

/**
 * @brief Выводит все контакты.
 * @param contacts Вектор контактов.
 */
void printContacts(const std::vector<Contact>& contacts);

/**
 * @brief Редактирует контакт.
 * @param contacts Вектор контактов.
 * @param indices Структура индекс-массивов.
 */
void editContact(std::vector<Contact>& contacts, IndexArray& indices);

/**
 * @brief Удаляет контакт.
 * @param contacts Вектор контактов.
 * @param indices Структура индекс-массивов.
 */
void deleteContact(std::vector<Contact>& contacts, IndexArray& indices);

int main() {
    std::vector<Contact> contacts;
    IndexArray indices;
    BinaryTree tree; // Создание экземпляра бинарного дерева

    // Создание экземпляра линейного списка
    // Изначально сортировка по имени и городу по возрастанию
    PrimarySortAttribute primaryAttr = PrimarySortAttribute::NAME;
    SecondarySortAttribute secondaryAttr = SecondarySortAttribute::CITY;
    SortOrder primaryOrder = SortOrder::ASCENDING;
    SortOrder secondaryOrder = SortOrder::ASCENDING;
    LinkedList sortedList(primaryAttr, secondaryAttr, primaryOrder, secondaryOrder);

    // Ввод данных контактов
    inputContacts(contacts);

    // Построение и сортировка индекс-массивов
    indices.buildIndices(contacts);
    indices.sortIndices();

    // Вставка данных в бинарное дерево по ключевому атрибуту (например, имя)
    for(const auto& contact : contacts) {
        tree.insert(contact.name, contact.id);
    }

    // Вставка данных в линейный список (сортированный)
    for(const auto& contact : contacts) {
        sortedList.insert(contact);
    }

    int choice;
    while(true) {
        std::cout << "\nМеню:\n"
                  << "1. Вывести все контакты\n"
                  << "2. Вывести контакты, отсортированные по имени (по возрастанию)\n"
                  << "3. Вывести контакты, отсортированные по имени (по убыванию)\n"
                  << "4. Вывести контакты, отсортированные по городу (по возрастанию)\n"
                  << "5. Вывести контакты, отсортированные по городу (по убыванию)\n"
                  << "6. Поиск контакта по имени (итерационный)\n"
                  << "7. Поиск контакта по имени (рекурсивный)\n"
                  << "8. Поиск контакта по городу (итерационный)\n"
                  << "9. Поиск контакта по городу (рекурсивный)\n"
                  << "10. Редактировать контакт\n"
                  << "11. Удалить контакт\n"
                  << "12. Вывести контакты из бинарного дерева по имени (по возрастанию)\n"
                  << "13. Вывести контакты из бинарного дерева по имени (по убыванию)\n"
                  << "14. Поиск контактов в бинарном дереве по имени\n"
                  << "15. Вывести контакты из линейного списка (сортированный)\n"
                  << "16. Поиск контактов в линейном списке (сортированный)\n"
                  << "17. Удалить контакт из линейного списка (сортированный)\n"
                  << "18. Изменить атрибуты сортировки линейного списка\n"
                  << "19. Сохранить линейный список в файл\n"
                  << "20. Загрузить линейный список из файла\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера

        if(choice == 0) {
            // Сохранение контактов перед выходом
            saveContactsToFile(contacts, "contacts.csv");
            // Сохранение линейного списка
            sortedList.saveToFile("linked_list.csv");
            break;
        }

        switch(choice) {
            case 1:
                printContacts(contacts);
                break;
            case 2:
                std::cout << "\nКонтакты, отсортированные по имени (по возрастанию):\n";
                printSortedByName(contacts, indices.nameIndexAsc);
                break;
            case 3:
                std::cout << "\nКонтакты, отсортированные по имени (по убыванию):\n";
                printSortedByName(contacts, indices.nameIndexDesc);
                break;
            case 4:
                std::cout << "\nКонтакты, отсортированные по городу (по возрастанию):\n";
                printSortedByCity(contacts, indices.cityIndexAsc);
                break;
            case 5:
                std::cout << "\nКонтакты, отсортированные по городу (по убыванию):\n";
                printSortedByCity(contacts, indices.cityIndexDesc);
                break;
            case 6: { // Поиск по имени (итерационный)
                std::string key;
                std::cout << "Введите имя для поиска (итерационный): ";
                std::getline(std::cin, key);
                std::vector<int> ids = binarySearchIterative(indices.nameIndexAsc, key);
                if(!ids.empty()) {
                    std::cout << "Найденные контакты с именем \"" << key << "\":\n";
                    for(auto id : ids) {
                        if(id - 1 < 0 || id - 1 >= contacts.size()) {
                            std::cerr << "Ошибка: Некорректный ID " << id << "\n";
                            continue;
                        }
                        const auto& contact = contacts[id - 1];
                        std::cout << "ID: " << contact.id << "\n"
                                  << "Имя: " << contact.name << "\n"
                                  << "Номер телефона: " << contact.phoneNumber << "\n"
                                  << "Город: " << contact.city << "\n"
                                  << "-----------------------------\n";
                    }
                }
                else {
                    std::cout << "Контакт с именем \"" << key << "\" не найден.\n";
                }
                break;
            }
            case 7: { // Поиск по имени (рекурсивный)
                std::string key;
                std::cout << "Введите имя для поиска (рекурсивный): ";
                std::getline(std::cin, key);
                std::vector<int> ids = binarySearchRecursive(indices.nameIndexAsc, key, 0, indices.nameIndexAsc.size() - 1);
                if(!ids.empty()) {
                    std::cout << "Найденные контакты с именем \"" << key << "\":\n";
                    for(auto id : ids) {
                        if(id - 1 < 0 || id - 1 >= contacts.size()) {
                            std::cerr << "Ошибка: Некорректный ID " << id << "\n";
                            continue;
                        }
                        const auto& contact = contacts[id - 1];
                        std::cout << "ID: " << contact.id << "\n"
                                  << "Имя: " << contact.name << "\n"
                                  << "Номер телефона: " << contact.phoneNumber << "\n"
                                  << "Город: " << contact.city << "\n"
                                  << "-----------------------------\n";
                    }
                }
                else {
                    std::cout << "Контакт с именем \"" << key << "\" не найден.\n";
                }
                break;
            }
            case 8: { // Поиск по городу (итерационный)
                std::string key;
                std::cout << "Введите город для поиска (итерационный): ";
                std::getline(std::cin, key);
                std::vector<int> ids = binarySearchIterative(indices.cityIndexAsc, key);
                if(!ids.empty()) {
                    std::cout << "Найденные контакты в городе \"" << key << "\":\n";
                    for(auto id : ids) {
                        if(id - 1 < 0 || id - 1 >= contacts.size()) {
                            std::cerr << "Ошибка: Некорректный ID " << id << "\n";
                            continue;
                        }
                        const auto& contact = contacts[id - 1];
                        std::cout << "ID: " << contact.id << "\n"
                                  << "Имя: " << contact.name << "\n"
                                  << "Номер телефона: " << contact.phoneNumber << "\n"
                                  << "Город: " << contact.city << "\n"
                                  << "-----------------------------\n";
                    }
                }
                else {
                    std::cout << "Контакт в городе \"" << key << "\" не найден.\n";
                }
                break;
            }
            case 9: { // Поиск по городу (рекурсивный)
                std::string key;
                std::cout << "Введите город для поиска (рекурсивный): ";
                std::getline(std::cin, key);
                std::vector<int> ids = binarySearchRecursive(indices.cityIndexAsc, key, 0, indices.cityIndexAsc.size() - 1);
                if(!ids.empty()) {
                    std::cout << "Найденные контакты в городе \"" << key << "\":\n";
                    for(auto id : ids) {
                        if(id - 1 < 0 || id - 1 >= contacts.size()) {
                            std::cerr << "Ошибка: Некорректный ID " << id << "\n";
                            continue;
                        }
                        const auto& contact = contacts[id - 1];
                        std::cout << "ID: " << contact.id << "\n"
                                  << "Имя: " << contact.name << "\n"
                                  << "Номер телефона: " << contact.phoneNumber << "\n"
                                  << "Город: " << contact.city << "\n"
                                  << "-----------------------------\n";
                    }
                }
                else {
                    std::cout << "Контакт в городе \"" << key << "\" не найден.\n";
                }
                break;
            }
            case 10:
                editContact(contacts, indices);
                // Перезапись бинарного дерева
                tree = BinaryTree(); // Перемещающее присваивание
                for(const auto& contact : contacts) {
                    tree.insert(contact.name, contact.id);
                }
                // Перезапись линейного списка
                sortedList = LinkedList(primaryAttr, secondaryAttr, primaryOrder, secondaryOrder); // Перемещающее присваивание
                for(const auto& contact : contacts) {
                    sortedList.insert(contact);
                }
                break;
            case 11:
                deleteContact(contacts, indices);
                // Перезапись бинарного дерева
                tree = BinaryTree(); // Перемещающее присваивание
                for(const auto& contact : contacts) {
                    tree.insert(contact.name, contact.id);
                }
                // Перезапись линейного списка
                sortedList = LinkedList(primaryAttr, secondaryAttr, primaryOrder, secondaryOrder); // Перемещающее присваивание
                for(const auto& contact : contacts) {
                    sortedList.insert(contact);
                }
                break;
            case 12: { // Вывод контактов из бинарного дерева по имени (по возрастанию)
                std::cout << "\nКонтакты из бинарного дерева по имени (по возрастанию):\n";
                tree.inOrder(contacts, true);
                break;
            }
            case 13: { // Вывод контактов из бинарного дерева по имени (по убыванию)
                std::cout << "\nКонтакты из бинарного дерева по имени (по убыванию):\n";
                tree.inOrder(contacts, false);
                break;
            }
            case 14: { // Поиск контактов в бинарном дереве по имени
                std::string key;
                std::cout << "Введите имя для поиска в бинарном дереве: ";
                std::getline(std::cin, key);
                std::vector<int> ids = tree.search(key);
                if(!ids.empty()) {
                    std::cout << "Найденные контакты с именем \"" << key << "\":\n";
                    for(auto id : ids) {
                        if(id - 1 < 0 || id - 1 >= contacts.size()) {
                            std::cerr << "Ошибка: Некорректный ID " << id << "\n";
                            continue;
                        }
                        const auto& contact = contacts[id - 1];
                        std::cout << "ID: " << contact.id << "\n"
                                  << "Имя: " << contact.name << "\n"
                                  << "Номер телефона: " << contact.phoneNumber << "\n"
                                  << "Город: " << contact.city << "\n"
                                  << "-----------------------------\n";
                    }
                }
                else {
                    std::cout << "Контакт с именем \"" << key << "\" не найден.\n";
                }
                break;
            }
            case 15: { // Вывод контактов из линейного списка (сортированный)
                std::cout << "\nКонтакты из линейного списка (сортированный):\n";
                sortedList.printSorted();
                break;
            }
            case 16: { // Поиск контактов в линейном списке (сортированный)
                std::string key;
                std::cout << "Введите " 
                          << (primaryAttr == PrimarySortAttribute::NAME ? "имя" : "город") 
                          << " для поиска в линейном списке (сортированный): ";
                std::getline(std::cin, key);
                sortedList.search(key);
                break;
            }
            case 17: { // Удаление контакта из линейного списка (сортированный)
                std::string key;
                std::cout << "Введите " 
                          << (primaryAttr == PrimarySortAttribute::NAME ? "имя" : "город") 
                          << " для удаления из линейного списка (сортированный): ";
                std::getline(std::cin, key);
                sortedList.remove(key);
                break;
            }
            case 18: { // Изменение атрибутов сортировки линейного списка
                int primaryAttrChoice, secondaryAttrChoice, primaryOrderChoice, secondaryOrderChoice;
                std::cout << "Выберите основной атрибут сортировки:\n"
                          << "1. Имя\n"
                          << "2. Город\n"
                          << "Ваш выбор: ";
                std::cin >> primaryAttrChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                PrimarySortAttribute newPrimaryAttr;
                if(primaryAttrChoice == 1)
                    newPrimaryAttr = PrimarySortAttribute::NAME;
                else if(primaryAttrChoice == 2)
                    newPrimaryAttr = PrimarySortAttribute::CITY;
                else {
                    std::cout << "Некорректный выбор. Возврат в меню.\n";
                    break;
                }

                std::cout << "Выберите второстепенный атрибут сортировки:\n"
                          << "1. Имя\n"
                          << "2. Город\n"
                          << "Ваш выбор: ";
                std::cin >> secondaryAttrChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                SecondarySortAttribute newSecondaryAttr;
                if(secondaryAttrChoice == 1)
                    newSecondaryAttr = SecondarySortAttribute::NAME;
                else if(secondaryAttrChoice == 2)
                    newSecondaryAttr = SecondarySortAttribute::CITY;
                else {
                    std::cout << "Некорректный выбор. Возврат в меню.\n";
                    break;
                }

                std::cout << "Выберите порядок сортировки для основного атрибута:\n"
                          << "1. По возрастанию\n"
                          << "2. По убыванию\n"
                          << "Ваш выбор: ";
                std::cin >> primaryOrderChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                SortOrder newPrimaryOrder;
                if(primaryOrderChoice == 1)
                    newPrimaryOrder = SortOrder::ASCENDING;
                else if(primaryOrderChoice == 2)
                    newPrimaryOrder = SortOrder::DESCENDING;
                else {
                    std::cout << "Некорректный выбор. Возврат в меню.\n";
                    break;
                }

                std::cout << "Выберите порядок сортировки для второстепенного атрибута:\n"
                          << "1. По возрастанию\n"
                          << "2. По убыванию\n"
                          << "Ваш выбор: ";
                std::cin >> secondaryOrderChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                SortOrder newSecondaryOrder;
                if(secondaryOrderChoice == 1)
                    newSecondaryOrder = SortOrder::ASCENDING;
                else if(secondaryOrderChoice == 2)
                    newSecondaryOrder = SortOrder::DESCENDING;
                else {
                    std::cout << "Некорректный выбор. Возврат в меню.\n";
                    break;
                }

                sortedList.changeSortAttributes(newPrimaryAttr, newSecondaryAttr, newPrimaryOrder, newSecondaryOrder);
                std::cout << "Атрибуты сортировки успешно изменены.\n";
                break;
            }
            case 19: { // Сохранение линейного списка в файл
                std::string filename;
                std::cout << "Введите имя файла для сохранения линейного списка: ";
                std::getline(std::cin, filename);
                sortedList.saveToFile(filename);
                break;
            }
            case 20: { // Загрузка линейного списка из файла
                std::string filename;
                std::cout << "Введите имя файла для загрузки линейного списка: ";
                std::getline(std::cin, filename);
                sortedList.loadFromFile(filename);
                break;
            }
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
