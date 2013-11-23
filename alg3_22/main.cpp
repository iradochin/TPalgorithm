/*
 *        Name: main.cpp
 *  Created on: Nov 17, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * Дано число N < 10^6 и последовательность пар целых чисел
 * из [-2^31..2^31] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся
 * парами чисел {Xi, Yi}. Каждая пара чисел {Xi, Yi} определяет ключ Xi
 * и приоритет Yi в декартовом дереве. Построить также наивное дерево поиска
 * по ключам Xi методом из задачи 1.
 *
 * 2_2. Вычислить количество узлов в самом широком слое
 * декартового дерева и количество узлов в самом широком слое
 * наивного дерева поиска. Вывести их разницу.
 */

/*
  10
  5 11
  18 8
  25 7
  50 12
  30 30
  15 15
  20 10
  22 5
  40 20
  45 9
*/

#include <iostream>

struct TreapNode
{
    int data;                    // NULL - если нет
    int priority;                // NULL - если нет
    TreapNode *left, *right;
    TreapNode(int dat, int value = 0): data(dat), priority(value),
        left(NULL), right(NULL) { }
    };

typedef TreapNode* pTreapNode;
void split(pTreapNode,const int, pTreapNode&, pTreapNode&);
void insertDecTree(pTreapNode&,const pTreapNode);
void insertBinaryTree (pTreapNode&,const int);
size_t getHeight(const TreapNode*);
size_t getWidth(const TreapNode*, const size_t);
size_t getMaxWidth(const TreapNode*);

int main()
{
    // N - количество элементов в дереве
    size_t N;
    std::cin >> N;

    // buf - число для добавления
    int x;
    std::cin >> x;

    // Зададим корень
    TreapNode* nodeBinary = new TreapNode(x);

    int y;
    std::cin >> y;

    TreapNode* nodeTreap = new TreapNode(x, y);

    // Вводим оставшиеся значения и добавляем в дерево
    for (size_t i = 1; i < N; ++i)
    {
        std::cin >> x;
        std::cin >> y;

        insertBinaryTree(nodeBinary, x);

        TreapNode* newNode = new TreapNode(x,y);
        insertDecTree(nodeTreap, newNode);
    }

    int one = getMaxWidth(nodeBinary);
    int two = getMaxWidth(nodeTreap);
//    int one = getHeight(nodeTreap);
//    int two = getHeight(nodeBinary);

    std::cout << two - one;

    return 0;
}

void split(pTreapNode in, const int data, pTreapNode& l, pTreapNode& r)
{
    // Разделяет дерево in на два дерева l и r,
    // таким образом, что l содержит все элементы, меньшие data,
    // а r содержит все элементы, большие или равные data.

    if (in == NULL)
    {
        // Если нашли точку разделения

        l = NULL;
        r = NULL;
    }
    else
        if (data < in->data)
        {
            // Определяем правое дерево r.

            split(in->left, data, l, in->left);
            r = in;
        }
        else
        {
            // Определяем левое дерево l.

            split(in->right, data, in->right, r);
            l = in;
        }
}

void insertDecTree(pTreapNode& root, const pTreapNode in)
{
    // Функция вставляет элемент in в декартово дерево с корнем root

    if (root == NULL)
    {
        // Если дошли до конца дерева

        root = in;
    }
    else
        if (in->priority > root->priority)
        {
            // Если нашли место - вызываем Split() от найденного элемента
            // (от элемента вместе со всем его поддеревом), и возвращаемые
            // им l и r деревья записываем в качестве левого и правого
            // сына добавляемого элемента.

            split(root, in->data, in->left, in->right);
            root = in;
        }
        else
            // Cпускаемся по дереву, и останавливаемся
            // на первом элементе, у которого значение приоритета
            // оказалось меньше in->priority.
            if (in->data < root->data)
            {
                insertDecTree(root->left, in);
            }
            else
            {
                insertDecTree(root->right, in);
            }
}

void insertBinaryTree(pTreapNode& in, const int data)
{
    // Рекурсивная вставка элемента в бинарное дерево заданное
    // наивным порядком вставки.

    if (in == NULL)
    {
        in = new TreapNode(data);
        return;
    }

    // Если новый ключ >= ,то помещаем его в правое поддерево, иначе в левое
    if (data >= in->data)
        insertBinaryTree(in->right, data);
    else
        insertBinaryTree(in->left, data);
}

size_t getHeight(const TreapNode *root)
{
    // Функция возвращает количество слоев в дереве

        if (root == NULL)
            // Если дерево пустое
            return 0;

        // Ищем глубину правого и левого поддерева и выбыраем максимальную
        // глубину + 1 (корень).

        size_t hLeft = 0, hRight = 0;
        if (root->left != NULL)
            hLeft = getHeight(root->left);

        if (root->right)
            hRight = getHeight(root->right);

        return std::max(hLeft, hRight) + 1;
}

size_t getWidth(const TreapNode* in, const size_t level)
{
    // Функция возвращает ширину слоя level дерева (слои начиная с нуля).

    if (in == NULL)
        // Если дерево пустое.
        return 0;

    if (level == 0)
        // Выход из рекурсии, если достигли необходимого слоя.
        return 1;

    if (level > 0)
        return getWidth(in->left, level - 1) + getWidth(in->right, level - 1);

    return 0;
}

size_t getMaxWidth(const TreapNode* root)
{
    // Функция возвращает максимальную ширину среди всех слоев дерева.

    size_t height = getHeight(root);
    size_t maxWidth = 0;
    for (size_t i = 0; i < height; ++i)
    {
        // Для каждого слоя ищем его ширину.

        size_t width = getWidth(root, i);
        if (maxWidth < width)
            maxWidth = width;
    }

    return maxWidth;
}
