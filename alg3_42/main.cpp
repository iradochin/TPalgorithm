/*
 *        Name: main.cpp
 *  Created on: Nov 23, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * 4_2. Порядковые статистики. Дана число N и N строк. Каждая строка
 * содержащит команду добавления или удаления натуральных чисел,
 * а также запрос на получение k-ой порядковой статистики.
 * Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”.
 * Запрос на получение k-ой порядковой статистики задается числом k.
 */

/*
 * 5
 * 40 0
 * 10 1
 * 4 1
 * -10 0
 * 50 2
 */

#include <iostream>
#include <cmath>

struct node
{
    int key;                            // Данные
    unsigned char height;               // Высота поддерева с корнем в этом узле
    size_t value;                       // Количество элементов
    node* left;                         // NULL - если нет
    node* right;                        // NULL - если нет
    node(int k) { key = k; left = right = NULL; value = 1; height = 1; }
};

unsigned char height(node*);
int balancefactor(node*);
void fixheight(node*);
node* rotateright(node*);
node* rotateleft(node*);
node* balance(node*);
node* insert(node*, const int);
node* findmin(node*);
node* removemin(node*);
node* remove(node*, const int);
size_t getNumberOfElements(const node*);
int kth(const node* root, size_t);
void deleteAll(node* root);

int main()
{
    // Вводим количество элементов
    size_t N;
    std::cin >> N;

    struct node* root = NULL;
    for (size_t i = 0; i < N; ++i)
    {
        int x;
        std::cin >> x;

        // х - элемент дерева, если положительный, то добавляем в дерево,
        // иначе - удаляем
        if (x > 0)
            root = insert(root, x);
        else
            root = remove(root, std::abs(x));

        // у - порядковый номер
        int y;
        std::cin >> y;
        std::cout << kth(root, y + 1) << "\n";
    }

    deleteAll(root);

    return 0;
}

unsigned char height(node* root)
{
    // Возвращает поле height или 0, если root == NULL

    return root ? root->height : 0;
}

int balancefactor(node* root)
{
    // Разница высот правого и левого поддерева, для балансировки

    return height(root->right) - height(root->left);
}

void fixheight(node* root)
{
    // Восстановление поля height

    unsigned char left = height(root->left);
    unsigned char right = height(root->right);

    // height - самое глубокое дерево
    root->height = ((left > right) ? left : right) + 1;

    // Считаем/пересчитывем количество элементов в дереве с корнем root
    root->value = getNumberOfElements(root);
}

node* rotateright(node* root)
{
    // Правый поворот вокруг root
    node* in = root->left;
    root->left = in->right;
    in->right = root;

    // Восстанавливаем высоты
    fixheight(root);
    fixheight(in);

    // Возвращает новый корень полученного дерева
    return in;
}

node* rotateleft(node* root)
{
    // Левый поворот вокруг root
    node* in = root->right;
    root->right = in->left;
    in->left = root;

    // Восстанавливаем высоты
    fixheight(root);
    fixheight(in);

    // Возвращаем новый корень полученного дерева
    return in;
}

node* balance(node* root)
{
    // Балансировка дерева

    fixheight(root);

    // Если высота правого дерева больше, чем левый, то поворачиваем влево
    if(balancefactor(root) == 2)
    {
        if(balancefactor(root->right) < 0)
            root->right = rotateright(root->right);

        return rotateleft(root);
    }

    // Если высота левого дерева больше, чем правого, то поворачиваем вправо
    if(balancefactor(root) == -2)
    {
        if(balancefactor(root->left) > 0)
            root->left = rotateleft(root->left);

        return rotateright(root);
    }

    // Если балансировка не нужна
    return root;
}

node* insert(node* root, const int k)
{
    // Вставка элемента в дерево

    if (root == NULL)
        return new node(k);

    // Спускаемся вниз по дереву, выбирая правое или левое направление
    // в зависимости от значения k
    if ( k < root->key )
    {
        root->left = insert(root->left, k);
    }
    else
    {
        root->right = insert(root->right, k);
    }

    // Выполняем балансровку узла
    return balance(root);
}

node* findmin(node* root)
{
    // Поиск минимального элемента в дереве с корнем root

    return root->left ? findmin(root->left) : root;
}

node* removemin(node* root)
{
    // Удаление узла с минимльным элементом в дереве с корнем root

    // Возвращаем указатель на правое дерево
    if( root->left == NULL )
        return root->right;

    root->left = removemin(root->left);

    // Выполняем балансировку
    return balance(root);
}

node* remove(node* root, const int k)
{
    // Удаление узла

    if(root == NULL)
        return NULL;

    // Находим необходимый узел
    if (k < root->key)
        root->left = remove(root->left, k);
    else
        if (k > root->key)
            root->right = remove(root->right, k);
        else
        {
            // Если у элемента нет потомков
            if (!root->left && !root->right)
            {
                delete root;

                return NULL;
            }

            // Если у элемента нет правого потомка
            if(!root->right)
            {
                node* left = root->left;
                delete root;

                return left;
            }

            // Если у элемента нет левого потомка
            if(!root->left)
            {
                node* right = root->right;
                delete root;

                return right;
            }

            // Если у элемента есть и правый, и левый потомок
            node* left = root->left;
            node* right = root->right;
            delete root;

            // Находим минимальный элемент в правом поддереве
            node* min = findmin(right);
            // Извлекаем минимальный
            min->right = removemin(right);
            min->left = left;

            // Выполняем балансировку и возвращаем min
            return balance(min);
        }

    // Выполняем балансировку
    return balance(root);
}

size_t getNumberOfElements(const node* root)
{
    // Функция возвращает количество элементов в дереве с корнем root

    if (root == NULL)
        // Если дерево пустое
        return 0;

    // Идем от самого низа и суммируем количество элементов в правом и
    // левом поддереве, если их нет, то присваеваем ему 1.
    size_t hLeft = 0, hRight = 0;
    if (root->left)
        hLeft = getNumberOfElements(root->left);

    if (root->right)
        hRight = getNumberOfElements(root->right);

    return hLeft + hRight + 1;
}

int kth(const node *root, size_t find)
{
    // Функция поиска Кй статистики в дереве с корнем root

    size_t num;

    // num - принимает значение своего порядкового номера, если в правом
    // поддереве никого нет, то совпадает со значением количества элемента,
    // иначе (т.к. справа все элементы больше текущего) разность всего
    // количества элементов в этом дереве и количества элементов справа.
    if (!root->right)
        num = root->value;
    else
        num = root->value - root->right->value;

    if (num == find)
        return root->key;

    if (num > find)
        return kth(root->left, find);

    // Если искомый элемент в правом поддереве уменьшаем его номер на текущий
    // номер элемента и идем в правое поддерево.
    if (num < find)
    {
        find -= num;
        return kth(root->right, find);
    }

    return -1;
}

void deleteAll(node* root)
{
    // Удаление всех элементов дерева.

    if (root != NULL)
        return;

    deleteAll(root->left);
    deleteAll(root->right);

    delete root;
}
