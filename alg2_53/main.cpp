/*
 *        Name: merge1.cpp
 *  Created on: Nov 7, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * 5.3 Binary MSD для long long.
 * Дан массив целых 64-разрядных чисел. Количество чисел не больше 106.
 * Отсортировать массив методом MSD по !!битам!! (бинарный QuickSort).
 */

#include <vector>
#include <iostream>

inline int bit ( long long, int );  // Возвращает бит числа
void quicksortBin( std::vector<long long>&, int, int, int ); // binary quicksort

int main ()
{
    int num;
    std::cin >> num;
    std::vector<long long> in (num);

    for (int i = 0; i < num; ++i )
    {
        std::cin >> in[i];
    }

    quicksortBin( in, 0, num - 1, 63 );

    for (int i = 0; i < num; ++i )
    {
        for ( int j = 63; j >=0 ; --j)
            std::cout << bit ( in[i], j );
        std::cout << " ";
        std::cout << in[i] << " ";
    }

    return 0;
}

inline int bit ( long long number, int d )
{
    return (number >> d) & 1;
}

void quicksortBin( std::vector<long long>& a, int l, int r, int d )
{
    // Работает пока l <= r, т.е. все элементы справа от a[i] имеют 1 в
    // d-й позиции, а все элементы слева имеют 0 в d-й позиции, или пока
    // не прошли по всем битам.
    if ( r <= l || d < 0)
        return;

    int i = l, j = r;

    // Ищем 0 бит и меняем это число с тем, которое имеет 1 в позиции == d.
    while ( i != j )
    {
        while ( bit(a[i] , d) == 0 && (i < j) )
            i++;

        while ( bit(a[j] , d) == 1 && (j > i) )
            j--;

        std::swap( a[i], a[j] );
    }

    // У среднего элемента в d-й позиции 0, то сдаигаем правую границу на 1.
    if ( bit(a[r], d) == 0 )
        j++;

    quicksortBin( a, l, j - 1, d - 1 );
    quicksortBin( a, j, r, d - 1 );
}
