// binary_tree.cpp

#include "binary_tree.h"
#include <algorithm>
#include <iostream>

// Конструктор
BinaryTree::BinaryTree() : root(nullptr) {}

// Перемещающий конструктор
BinaryTree::BinaryTree(BinaryTree&& other) noexcept
    : root(std::move(other.root)) {}

// Перемещающий оператор присваивания
BinaryTree& BinaryTree::operator=(BinaryTree&& other) noexcept {
    if(this != &other) {
        root = std::move(other.root);
    }
    return *this;
}

// Деструктор
BinaryTree::~BinaryTree() {
    // Умные указатели автоматически освобождают память
}

// Получение высоты узла
int BinaryTree::getHeight(TreeNode* node) const {
    return node ? node->height : 0;
}

// Получение баланса узла
int BinaryTree::getBalance(TreeNode* node) const {
    if(!node) return 0;
    return getHeight(node->left.get()) - getHeight(node->right.get());
}

// Правый поворот
TreeNode* BinaryTree::rightRotate(TreeNode* y) {
    TreeNode* x = y->left.release();
    TreeNode* T2 = x->right.release();

    // Выполнение поворота
    x->right.reset(y);
    y->left.reset(T2);

    // Обновление высот
    y->height = std::max(getHeight(y->left.get()), getHeight(y->right.get())) + 1;
    x->height = std::max(getHeight(x->left.get()), getHeight(x->right.get())) + 1;

    // Возврат нового корня
    return x;
}

// Левый поворот
TreeNode* BinaryTree::leftRotate(TreeNode* x) {
    TreeNode* y = x->right.release();
    TreeNode* T2 = y->left.release();

    // Выполнение поворота
    y->left.reset(x);
    x->right.reset(T2);

    // Обновление высот
    x->height = std::max(getHeight(x->left.get()), getHeight(x->right.get())) + 1;
    y->height = std::max(getHeight(y->left.get()), getHeight(y->right.get())) + 1;

    // Возврат нового корня
    return y;
}

// Находит узел с минимальным ключом
TreeNode* BinaryTree::findMin(TreeNode* node) const {
    TreeNode* current = node;
    while(current->left)
        current = current->left.get();
    return current;
}

// Вставка узла с балансировкой
TreeNode* BinaryTree::insert(TreeNode* node, const std::string& key, int recordNumber) {
    // Стандартная вставка в BST
    if(!node)
        return new TreeNode(key, recordNumber);
    if(key < node->key)
        node->left.reset(insert(node->left.release(), key, recordNumber));
    else if(key > node->key)
        node->right.reset(insert(node->right.release(), key, recordNumber));
    else { // key == node->key
        node->recordNumbers.push_back(recordNumber);
        return node;
    }

    // Обновление высоты этого узла
    node->height = 1 + std::max(getHeight(node->left.get()), getHeight(node->right.get()));

    // Получение баланса этого узла для проверки балансировки
    int balance = getBalance(node);

    // Если узел несбалансирован, то есть 4 случая

    // Left Left Case
    if(balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if(balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if(balance > 1 && key > node->left->key) {
        node->left.reset(leftRotate(node->left.release()));
        return rightRotate(node);
    }

    // Right Left Case
    if(balance < -1 && key < node->right->key) {
        node->right.reset(rightRotate(node->right.release()));
        return leftRotate(node);
    }

    // Возврат (не изменённый) указатель узла
    return node;
}

// Вставка внешним интерфейсом
void BinaryTree::insert(const std::string& key, int recordNumber) {
    root.reset(insert(root.release(), key, recordNumber));
}

// Удаление узла с балансировкой
TreeNode* BinaryTree::deleteNode(TreeNode* node, const std::string& key, int recordNumber) {
    // Стандартное удаление в BST
    if(!node)
        return node;

    if(key < node->key)
        node->left.reset(deleteNode(node->left.release(), key, recordNumber));
    else if(key > node->key)
        node->right.reset(deleteNode(node->right.release(), key, recordNumber));
    else {
        // Удаление recordNumber из вектора
        node->recordNumbers.erase(
            std::remove(node->recordNumbers.begin(), node->recordNumbers.end(), recordNumber),
            node->recordNumbers.end()
        );

        // Если нет записей, удаляем узел
        if(node->recordNumbers.empty()) {
            // Узел с одним или нулём дочерних узлов
            if((node->left == nullptr) || (node->right == nullptr)) {
                TreeNode* temp = node->left ? node->left.release() : node->right.release();

                // Нет дочерних узлов
                if(!temp) {
                    delete node;
                    return nullptr;
                }
                else { // Один дочерний узел
                    delete node;
                    return temp;
                }
            }
            else {
                // Узел с двумя дочерними узлами
                TreeNode* temp = findMin(node->right.get());
                node->key = temp->key;
                node->recordNumbers = temp->recordNumbers;
                node->right.reset(deleteNode(node->right.release(), temp->key, temp->recordNumbers[0]));
            }
        }
        else {
            // Узел остаётся, так как есть записи
            return node;
        }
    }

    // Если дерево имело только один узел
    if(!node)
        return node;

    // Обновление высоты узла
    node->height = 1 + std::max(getHeight(node->left.get()), getHeight(node->right.get()));

    // Получение баланса узла
    int balance = getBalance(node);

    // Балансировка дерева

    // Left Left Case
    if(balance > 1 && getBalance(node->left.get()) >= 0)
        return rightRotate(node);

    // Left Right Case
    if(balance > 1 && getBalance(node->left.get()) < 0) {
        node->left.reset(leftRotate(node->left.release()));
        return rightRotate(node);
    }

    // Right Right Case
    if(balance < -1 && getBalance(node->right.get()) <= 0)
        return leftRotate(node);

    // Right Left Case
    if(balance < -1 && getBalance(node->right.get()) > 0) {
        node->right.reset(rightRotate(node->right.release()));
        return leftRotate(node);
    }

    return node;
}

// Удаление внешним интерфейсом
void BinaryTree::remove(const std::string& key, int recordNumber) {
    root.reset(deleteNode(root.release(), key, recordNumber));
}

// Поиск узла в поддереве
TreeNode* BinaryTree::search(TreeNode* node, const std::string& key) const {
    if(node == nullptr || node->key == key)
        return node;
    if(key < node->key)
        return search(node->left.get(), key);
    else
        return search(node->right.get(), key);
}

// Поиск внешним интерфейсом
std::vector<int> BinaryTree::search(const std::string& key) const {
    TreeNode* foundNode = search(root.get(), key);
    if(foundNode != nullptr) {
        return foundNode->recordNumbers;
    }
    else {
        return {};
    }
}

// Обход дерева (in-order)
void BinaryTree::inOrderTraversal(TreeNode* node, const std::vector<Contact>& contacts, bool ascending) const {
    if (node == nullptr) return;
    if (ascending) {
        inOrderTraversal(node->left.get(), contacts, ascending);
    }
    else {
        inOrderTraversal(node->right.get(), contacts, ascending);
    }

    // Вывод всех записей в узле
    for(auto id : node->recordNumbers) {
        if(id - 1 >= 0 && id - 1 < contacts.size()) {
            const auto& contact = contacts[id - 1];
            std::cout << "ID: " << contact.id << "\n"
                      << "Имя: " << contact.name << "\n"
                      << "Номер телефона: " << contact.phoneNumber << "\n"
                      << "Город: " << contact.city << "\n"
                      << "-----------------------------\n";
        }
    }

    if (ascending) {
        inOrderTraversal(node->right.get(), contacts, ascending);
    }
    else {
        inOrderTraversal(node->left.get(), contacts, ascending);
    }
}

// Обход дерева внешним интерфейсом
void BinaryTree::inOrder(const std::vector<Contact>& contacts, bool ascending) const {
    inOrderTraversal(root.get(), contacts, ascending);
}
