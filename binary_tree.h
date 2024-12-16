// binary_tree.h

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "contact.h" // Для доступа к структуре Contact
#include <string>
#include <vector>
#include <memory>

/**
 * @struct TreeNode
 * @brief Узел AVL-дерева, содержащий ключ, номера записей и указатели на дочерние узлы.
 */
struct TreeNode {
    std::string key;                ///< Ключ узла (например, имя)
    std::vector<int> recordNumbers; ///< Номера записей с этим ключом
    std::unique_ptr<TreeNode> left; ///< Левый дочерний узел
    std::unique_ptr<TreeNode> right;///< Правый дочерний узел
    int height;                     ///< Высота узла для балансировки

    /**
     * @brief Конструктор узла.
     * @param key Ключ узла.
     * @param recordNumber Номер записи.
     */
    TreeNode(const std::string& key, int recordNumber)
        : key(key), recordNumbers{ recordNumber }, height(1) {}
};

/**
 * @class BinaryTree
 * @brief Класс для управления сбалансированным AVL-деревом.
 */
class BinaryTree {
private:
    std::unique_ptr<TreeNode> root; ///< Корень дерева

    // Вспомогательные функции

    /**
     * @brief Вставляет ключ и номер записи в поддерево.
     * @param node Текущий узел поддерева.
     * @param key Ключ для вставки.
     * @param recordNumber Номер записи.
     * @return Указатель на узел после вставки и балансировки.
     */
    TreeNode* insert(TreeNode* node, const std::string& key, int recordNumber);

    /**
     * @brief Удаляет номер записи из поддерева.
     * @param node Текущий узел поддерева.
     * @param key Ключ для удаления.
     * @param recordNumber Номер записи.
     * @return Указатель на узел после удаления и балансировки.
     */
    TreeNode* deleteNode(TreeNode* node, const std::string& key, int recordNumber);

    /**
     * @brief Ищет узел с заданным ключом в поддереве.
     * @param node Текущий узел поддерева.
     * @param key Ключ для поиска.
     * @return Указатель на найденный узел или nullptr.
     */
    TreeNode* search(TreeNode* node, const std::string& key) const;

    /**
     * @brief Выполняет обход дерева в порядке in-order и выводит контакты.
     * @param node Текущий узел поддерева.
     * @param contacts Вектор контактов.
     * @param ascending Порядок обхода: true - по возрастанию, false - по убыванию.
     */
    void inOrderTraversal(TreeNode* node, const std::vector<Contact>& contacts, bool ascending) const;

    // Функции для балансировки

    /**
     * @brief Получает высоту узла.
     * @param node Узел для получения высоты.
     * @return Высота узла.
     */
    int getHeight(TreeNode* node) const;

    /**
     * @brief Вычисляет баланс узла.
     * @param node Узел для вычисления баланса.
     * @return Баланс узла (разница высот левого и правого поддеревьев).
     */
    int getBalance(TreeNode* node) const;

    /**
     * @brief Выполняет правый поворот.
     * @param y Узел для поворота.
     * @return Новый корень поддерева после поворота.
     */
    TreeNode* rightRotate(TreeNode* y);

    /**
     * @brief Выполняет левый поворот.
     * @param x Узел для поворота.
     * @return Новый корень поддерева после поворота.
     */
    TreeNode* leftRotate(TreeNode* x);

    /**
     * @brief Находит узел с минимальным ключом в поддереве.
     * @param node Корень поддерева.
     * @return Указатель на узел с минимальным ключом.
     */
    TreeNode* findMin(TreeNode* node) const;

public:
    /**
     * @brief Конструктор класса BinaryTree.
     */
    BinaryTree();

    /**
     * @brief Перемещающий конструктор.
     * @param other Другой объект BinaryTree для перемещения.
     */
    BinaryTree(BinaryTree&& other) noexcept;

    /**
     * @brief Перемещающий оператор присваивания.
     * @param other Другой объект BinaryTree для перемещения.
     * @return Ссылка на текущий объект.
     */
    BinaryTree& operator=(BinaryTree&& other) noexcept;

    // Удаление копирующих конструкторов и операторов
    BinaryTree(const BinaryTree& other) = delete;
    BinaryTree& operator=(const BinaryTree& other) = delete;

    /**
     * @brief Деструктор класса BinaryTree.
     */
    ~BinaryTree();

    /**
     * @brief Вставляет ключ и номер записи в дерево.
     * @param key Ключ для вставки.
     * @param recordNumber Номер записи.
     */
    void insert(const std::string& key, int recordNumber);

    /**
     * @brief Удаляет номер записи из дерева.
     * @param key Ключ для удаления.
     * @param recordNumber Номер записи.
     */
    void remove(const std::string& key, int recordNumber);

    /**
     * @brief Выполняет обход дерева и выводит контакты.
     * @param contacts Вектор контактов.
     * @param ascending Порядок обхода: true - по возрастанию, false - по убыванию.
     */
    void inOrder(const std::vector<Contact>& contacts, bool ascending = true) const;

    /**
     * @brief Ищет контакты по ключу.
     * @param key Ключ для поиска.
     * @return Вектор ID найденных контактов.
     */
    std::vector<int> search(const std::string& key) const;
};

#endif // BINARY_TREE_H
