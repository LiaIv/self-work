// contact.h

#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>

// Глобальный счётчик для уникальных ID
extern int global_id_counter;

/**
 * @struct Contact
 * @brief Структура для хранения информации о контакте.
 */
struct Contact {
    int id;                         ///< Уникальный ID контакта
    std::string name;               ///< Имя контакта
    std::string phoneNumber;        ///< Номер телефона
    std::string city;               ///< Город
};

/**
 * @struct Index
 * @brief Структура для хранения индекса.
 */
struct Index {
    std::string key;      ///< Значение атрибута (имя или город)
    int recordNumber;     ///< Номер записи в основном массиве
};

/**
 * @struct IndexArray
 * @brief Структура для хранения индекс-массивов.
 */
struct IndexArray {
    std::vector<Index> nameIndexAsc;       ///< Индекс по имени по возрастанию
    std::vector<Index> nameIndexDesc;      ///< Индекс по имени по убыванию
    std::vector<Index> cityIndexAsc;       ///< Индекс по городу по возрастанию
    std::vector<Index> cityIndexDesc;      ///< Индекс по городу по убыванию

    /**
     * @brief Создаёт индексы на основе контактов.
     * @param contacts Вектор контактов.
     */
    void buildIndices(const std::vector<Contact>& contacts);

    /**
     * @brief Сортирует индекс-массивы.
     */
    void sortIndices();
};

// Объявления функций

/**
 * @brief Вводит данные контактов с валидацией.
 * @param contacts Вектор для хранения контактов.
 */
void inputContacts(std::vector<Contact>& contacts);

/**
 * @brief Выводит все контакты.
 * @param contacts Вектор контактов.
 */
void printContacts(const std::vector<Contact>& contacts);

/**
 * @brief Выводит контакты, отсортированные по имени.
 * @param contacts Вектор контактов.
 * @param nameIndex Отсортированный индекс по имени.
 */
void printSortedByName(const std::vector<Contact>& contacts, const std::vector<Index>& nameIndex);

/**
 * @brief Выводит контакты, отсортированные по городу.
 * @param contacts Вектор контактов.
 * @param cityIndex Отсортированный индекс по городу.
 */
void printSortedByCity(const std::vector<Contact>& contacts, const std::vector<Index>& cityIndex);

/**
 * @brief Итеративный бинарный поиск по индекс-массиву.
 * @param indexArray Отсортированный индекс-массив.
 * @param key Ключ для поиска.
 * @return Вектор ID найденных контактов.
 */
std::vector<int> binarySearchIterative(const std::vector<Index>& indexArray, const std::string& key);

/**
 * @brief Рекурсивный бинарный поиск по индекс-массиву.
 * @param indexArray Отсортированный индекс-массив.
 * @param key Ключ для поиска.
 * @param left Левая граница поиска.
 * @param right Правая граница поиска.
 * @return Вектор ID найденных контактов.
 */
std::vector<int> binarySearchRecursive(const std::vector<Index>& indexArray, const std::string& key, int left, int right);

/**
 * @brief Редактирует контакт по имени.
 * @param contacts Вектор контактов.
 * @param indices Структура индекс-массивов.
 */
void editContact(std::vector<Contact>& contacts, IndexArray& indices);

/**
 * @brief Удаляет контакт по имени.
 * @param contacts Вектор контактов.
 * @param indices Структура индекс-массивов.
 */
void deleteContact(std::vector<Contact>& contacts, IndexArray& indices);

/**
 * @brief Проверяет, не пустое ли имя.
 * @param name Имя для проверки.
 * @return true, если имя не пустое, иначе false.
 */
bool validateName(const std::string& name);

/**
 * @brief Проверяет, не пустой ли город.
 * @param city Город для проверки.
 * @return true, если город не пустой, иначе false.
 */
bool validateCity(const std::string& city);

/**
 * @brief Проверяет формат номера телефона.
 * @param phoneNumber Номер телефона для проверки.
 * @return true, если формат корректный, иначе false.
 */
bool validatePhoneNumber(const std::string& phoneNumber);

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

#endif // CONTACT_H
