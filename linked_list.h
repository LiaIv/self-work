// linked_list.h

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "contact.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

/**
 * @enum PrimarySortAttribute
 * @brief Перечисление для основного атрибута сортировки.
 */
enum class PrimarySortAttribute {
    NAME, ///< Сортировка по имени
    CITY  ///< Сортировка по городу
};

/**
 * @enum SecondarySortAttribute
 * @brief Перечисление для второстепенного атрибута сортировки.
 */
enum class SecondarySortAttribute {
    NAME, ///< Сортировка по имени
    CITY  ///< Сортировка по городу
};

/**
 * @enum SortOrder
 * @brief Перечисление для порядка сортировки.
 */
enum class SortOrder {
    ASCENDING,  ///< По возрастанию
    DESCENDING  ///< По убыванию
};

/**
 * @struct ListNode
 * @brief Узел линейного списка, содержащий контакт и указатель на следующий узел.
 */
struct ListNode {
    Contact contact;                    ///< Объект контакта
    std::unique_ptr<ListNode> next;     ///< Указатель на следующий узел

    /**
     * @brief Конструктор узла.
     * @param contact Объект контакта для хранения в узле.
     */
    ListNode(const Contact& contact) : contact(contact), next(nullptr) {}
};

/**
 * @class LinkedList
 * @brief Класс для управления линейным списком с сортировкой по двум атрибутам.
 */
class LinkedList {
private:
    std::unique_ptr<ListNode> head;                ///< Голова списка
    PrimarySortAttribute primaryAttribute;         ///< Основной атрибут сортировки
    SecondarySortAttribute secondaryAttribute;     ///< Второстепенный атрибут сортировки
    SortOrder primaryOrder;                        ///< Порядок сортировки основного атрибута
    SortOrder secondaryOrder;                      ///< Порядок сортировки второстепенного атрибута

    /**
     * @brief Сравнивает два контакта на основе текущих атрибутов и порядка сортировки.
     * @param a Первый контакт для сравнения.
     * @param b Второй контакт для сравнения.
     * @return true, если a должен быть перед b, иначе false.
     */
    bool compare(const Contact& a, const Contact& b) const;

public:
    /**
     * @brief Конструктор класса LinkedList.
     * @param primaryAttr Основной атрибут сортировки.
     * @param secondaryAttr Второстепенный атрибут сортировки.
     * @param primaryOrd Порядок сортировки основного атрибута.
     * @param secondaryOrd Порядок сортировки второстепенного атрибута.
     */
    LinkedList(PrimarySortAttribute primaryAttr, SecondarySortAttribute secondaryAttr,
               SortOrder primaryOrd, SortOrder secondaryOrd);

    /**
     * @brief Перемещающий конструктор.
     * @param other Другой объект LinkedList для перемещения.
     */
    LinkedList(LinkedList&& other) noexcept;

    /**
     * @brief Перемещающий оператор присваивания.
     * @param other Другой объект LinkedList для перемещения.
     * @return Ссылка на текущий объект.
     */
    LinkedList& operator=(LinkedList&& other) noexcept;

    // Удаление копирующего конструктора и оператора присваивания
    LinkedList(const LinkedList& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;

    /**
     * @brief Деструктор класса LinkedList.
     * Освобождает память, занятую узлами списка.
     */
    ~LinkedList();

    /**
     * @brief Вставляет новый контакт в список с учётом сортировки.
     * @param contact Контакт для вставки.
     */
    void insert(const Contact& contact);

    /**
     * @brief Выводит список контактов в порядке сортировки.
     */
    void printSorted() const;

    /**
     * @brief Выводит список контактов в порядке их вставки.
     * (Требует дополнительной реализации для сохранения порядка вставки)
     */
    void printInsertionOrder() const;

    /**
     * @brief Ищет и выводит контакты с заданным значением атрибута.
     * @param key Значение атрибута для поиска.
     */
    void search(const std::string& key) const;

    /**
     * @brief Удаляет контакт с заданным значением атрибута.
     * @param key Значение атрибута для удаления.
     */
    void remove(const std::string& key);

    /**
     * @brief Изменяет атрибуты сортировки и пересортировывает список.
     * @param primaryAttr Новый основной атрибут сортировки.
     * @param secondaryAttr Новый второстепенный атрибут сортировки.
     * @param primaryOrd Новый порядок сортировки основного атрибута.
     * @param secondaryOrd Новый порядок сортировки второстепенного атрибута.
     */
    void changeSortAttributes(PrimarySortAttribute primaryAttr, SecondarySortAttribute secondaryAttr,
                              SortOrder primaryOrd, SortOrder secondaryOrd);

    /**
     * @brief Сохраняет список контактов в файл.
     * @param filename Имя файла для сохранения.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Загружает список контактов из файла.
     * @param filename Имя файла для загрузки.
     */
    void loadFromFile(const std::string& filename);
};

#endif // LINKED_LIST_H
