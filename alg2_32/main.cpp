/*
 *        Name: main.cpp
 *  Created on: Nov 4, 2013
 *      Author: roland
 *	 Copiright: 2013 All rights reserved
 */

/*
 * Даны неотрицательные целые числа n,k и массив целых сичел из [0..10^9]
 * размера n. Требуется найти k-ю порядковую статистику. т.е.
 * напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
 * в отсортированном массиве. Напишите нерекурсивный алгоритм.
 * Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 *
 * 3.2
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами
 * от конца массива к началу.
 */

#include <iostream>
#include <vector>
//#include <algorithm>

void medianOfThree (std::vector<int>&, int, int );
int partition ( std::vector <int> &, int, int );
int kStat ( std::vector<int>&, int, int, int );

int main ()
{
    int n = 0;
    std::cin >> n;
    int k = 0;
    std::cin >> k;
    std::vector<int> a( n, 0 );
    for ( int i = 0; i < n ; ++i )
    {
        std::cin >> a[i];
    }

    std::cout << kStat ( a, 0, n - 1, k );

//    nth_element ( a.begin(), a.begin() + k, a.end() );
//    std::cout << a[k];
}

void medianOfThree (std::vector<int>& a, int left, int right)
{
    if ( a[( left + right ) / 2] > a[right] )
        std::swap ( a[( left + right ) / 2], a[right] );
    if ( a[left] < a[( left + right ) / 2] )
        std::swap ( a[left], a[( left + right ) / 2] );
    if ( a[left] > a[right] )
        std::swap ( a[left], a[right] );
}

int partition ( std::vector <int> &a, int left, int right )
{
    medianOfThree( a, left, right );
    int i = right;
    int j = right;
    int flag = 0;

    while ( j > left )
    {
        while ( a[left] == a[j] && j > left )
        {
            if ( flag % 2 )
            {
                std::swap(a[i], a[j]);
                --i;
                --j;
            }
            else
            {
                --j;
            }
            flag++;
        }

        while ( a[j] < a[left] && j > left )
            --j;

        while ( a[j] > a[left] && j > left )
        {
            std::swap( a[j], a[i] );
            --i;
            --j;
        }
    }
    std::swap ( a[left], a[i] );

    return i;
}

int kStat ( std::vector<int>& a, int left, int right, int k )
{
    int l = left;
    int r = right;
    int p = -1;
    while ( p != k )
    {
        p = partition ( a, l, r );
        if ( p < k )
            l = p + 1;
        else
            r = p - 1;
    }

    return a[k];
    }
