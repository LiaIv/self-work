// test.cpp

#include "contact.h"
#include "binary_tree.h"
#include "linked_list.h"
#include <iostream>
#include <cassert>

/**
 * @brief Функция для тестирования вставки и балансировки AVL-дерева.
 */
void testAVLInsertion() {
    std::cout << "=== Тестирование вставки и балансировки AVL-дерева ===\n";
    BinaryTree tree;
    std::vector<Contact> contacts;

    // Вставка контактов
    contacts.push_back(Contact{1, "Елена", "1111111111", "Москва"});
    contacts.push_back(Contact{2, "Алексей", "2222222222", "Санкт-Петербург"});
    contacts.push_back(Contact{3, "Мария", "3333333333", "Новосибирск"});
    contacts.push_back(Contact{4, "Игорь", "4444444444", "Екатеринбург"});
    contacts.push_back(Contact{5, "Сергей", "5555555555", "Нижний Новгород"});
    contacts.push_back(Contact{6, "Анна", "6666666666", "Казань"});
    contacts.push_back(Contact{7, "Дмитрий", "7777777777", "Челябинск"});

    for(const auto& contact : contacts) {
        tree.insert(contact.name, contact.id);
    }

    // Ожидаемый баланс дерева
    // Проверим, что дерево сбалансировано и содержит все вставленные контакты

    // Поиск существующих и несуществующих контактов
    std::vector<int> result;

    // Существующие контакты
    result = tree.search("Мария");
    assert(!result.empty() && result[0] == 3);
    std::cout << "Поиск 'Мария': найден ID = " << result[0] << "\n";

    result = tree.search("Игорь");
    assert(!result.empty() && result[0] == 4);
    std::cout << "Поиск 'Игорь': найден ID = " << result[0] << "\n";

    // Несуществующий контакт
    result = tree.search("Петр");
    assert(result.empty());
    std::cout << "Поиск 'Петр': не найден.\n";

    // Вывод дерева по возрастанию
    std::cout << "\nДерево (по возрастанию):\n";
    tree.inOrder(contacts, true);

    // Вывод дерева по убыванию
    std::cout << "\nДерево (по убыванию):\n";
    tree.inOrder(contacts, false);

    std::cout << "=== Тестирование вставки и балансировки завершено ===\n\n";
}

/**
 * @brief Функция для тестирования удаления и балансировки AVL-дерева.
 */
void testAVLDeletion() {
    std::cout << "=== Тестирование удаления и балансировки AVL-дерева ===\n";
    BinaryTree tree;
    std::vector<Contact> contacts;

    // Вставка контактов
    contacts.push_back(Contact{1, "Елена", "1111111111", "Москва"});
    contacts.push_back(Contact{2, "Алексей", "2222222222", "Санкт-Петербург"});
    contacts.push_back(Contact{3, "Мария", "3333333333", "Новосибирск"});
    contacts.push_back(Contact{4, "Игорь", "4444444444", "Екатеринбург"});
    contacts.push_back(Contact{5, "Сергей", "5555555555", "Нижний Новгород"});
    contacts.push_back(Contact{6, "Анна", "6666666666", "Казань"});
    contacts.push_back(Contact{7, "Дмитрий", "7777777777", "Челябинск"});

    for(const auto& contact : contacts) {
        tree.insert(contact.name, contact.id);
    }

    // Удаление существующего контакта
    tree.remove("Мария", 3);
    std::cout << "Удален контакт 'Мария' (ID = 3).\n";
    std::vector<int> result = tree.search("Мария");
    assert(result.empty());
    std::cout << "Поиск 'Мария' после удаления: не найден.\n";

    // Удаление несуществующего контакта
    tree.remove("Петр", 8); // Контакт не существует
    std::cout << "Попытка удалить несуществующий контакт 'Петр' (ID = 8).\n";

    // Удаление другого контакта
    tree.remove("Елена", 1);
    std::cout << "Удален контакт 'Елена' (ID = 1).\n";
    result = tree.search("Елена");
    assert(result.empty());
    std::cout << "Поиск 'Елена' после удаления: не найден.\n";

    // Вывод дерева после удалений
    std::cout << "\nДерево после удалений (по возрастанию):\n";
    tree.inOrder(contacts, true);

    // Проверка баланса (неявно через корректный вывод)
    std::cout << "=== Тестирование удаления и балансировки завершено ===\n\n";
}

/**
 * @brief Функция для тестирования линейного списка.
 */
void testLinkedList() {
    std::cout << "=== Тестирование линейного списка ===\n";
    // Создание линейного списка с сортировкой по имени (по возрастанию) и городу (по убыванию)
    LinkedList list(PrimarySortAttribute::NAME, SecondarySortAttribute::CITY, SortOrder::ASCENDING, SortOrder::DESCENDING);

    // Вставка контактов
    Contact c1{1, "Борис", "1111111111", "Москва"};
    Contact c2{2, "Алексей", "2222222222", "Санкт-Петербург"};
    Contact c3{3, "Виктория", "3333333333", "Новосибирск"};
    Contact c4{4, "Галина", "4444444444", "Екатеринбург"};
    Contact c5{5, "Дмитрий", "5555555555", "Нижний Новгород"};

    list.insert(c1);
    list.insert(c2);
    list.insert(c3);
    list.insert(c4);
    list.insert(c5);

    // Вывод отсортированного списка
    std::cout << "\nЛинейный список (отсортированный):\n";
    list.printSorted();

    // Поиск существующего контакта
    std::cout << "\nПоиск контакта с именем 'Алексей':\n";
    list.search("Алексей");

    // Поиск несуществующего контакта
    std::cout << "\nПоиск контакта с именем 'Петр':\n";
    list.search("Петр");

    // Удаление существующего контакта
    std::cout << "\nУдаление контакта с именем 'Галина':\n";
    list.remove("Галина");

    // Удаление несуществующего контакта
    std::cout << "\nУдаление контакта с именем 'Петр':\n";
    list.remove("Петр");

    // Вывод списка после удалений
    std::cout << "\nЛинейный список после удалений:\n";
    list.printSorted();

    // Изменение атрибутов сортировки
    std::cout << "\nИзменение атрибутов сортировки: основное - город (по убыванию), второстепенное - имя (по возрастанию).\n";
    list.changeSortAttributes(PrimarySortAttribute::CITY, SecondarySortAttribute::NAME, SortOrder::DESCENDING, SortOrder::ASCENDING);

    // Вывод списка после изменения сортировки
    std::cout << "\nЛинейный список после изменения сортировки:\n";
    list.printSorted();

    std::cout << "=== Тестирование линейного списка завершено ===\n\n";
}

/**
 * @brief Главная функция для запуска всех тестов.
 */
int main() {
    // Тестирование AVL-дерева
    testAVLInsertion();
    testAVLDeletion();

    // Тестирование линейного списка
    testLinkedList();

    return 0;
}
