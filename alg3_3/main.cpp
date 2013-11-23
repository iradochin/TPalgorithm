/*
 *        Name: main.cpp
 *  Created on: Nov 23, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * Дописать АВЛ-дерево. Методы повороты и удаление.
 * Дана последовательность команд добавления или удаления
 * натуральных чисел в АВЛ-дерево. Команда добавления числа A
 * задается положительным числом A, команда удаления числа A задается
 * отрицательным числом “-A”. Требуется вывести высоту АВЛ-дерева
 * после выполнения всех команд.
 */

#include <iostream>
#include <cmath>

struct node
{
    int key;                            // Данные
    unsigned char height;               // Высота поддерева с корнем в этом узле
    node* left;                         // NULL - если нет
    node* right;                        // NULL - если нет
    node(int k) { key = k; left = right = 0; height = 1; }
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

int main()
{
    struct node* root = NULL;

    // Считываем, пока не конец файла
    while (!std::cin.eof())
    {
        int buf;
        std::cin >> buf;

        // Если число положительное - добавляем элемент в дерево, иначе
        // извлекаем его
        if (buf > 0)
            root = insert(root, buf);
        else
            root = remove(root, std::abs(buf));
    }

    std::cout << (int)root->height;

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
        root->left = insert(root->left, k);
    else
        root->right = insert(root->right, k);

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
