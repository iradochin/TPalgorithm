/*
 *        Name: main.cpp
 *  Created on: Nov 5, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * 4.1 Первые k элементов длинной последовательности.
 * Дана очень длинная последовательность целых чисел длины n.
 * Требуется вывести в отсортированном виде её первые
 * k элементов. Последовательность может не помещаться
 * в память. Время работы O(n * log(k)).
 * Доп. память O(k). Использовать слияние.
 *
 */

/*
 * 9 4
 * 3 7 4 5 6 1 15 4 2
 *
 * 1 2 3 4
 */

#include <iostream>
#include <vector>
#include <stdint.h>
#include <algorithm>


void merge( std::vector<int> &mas, int l, int m, int r )
{
    std::vector<int> buffer( r - l + 1 );
    int pos1 = l;
    int pos2 = m + 1;
    int posB = 0;
    while ( pos1 <= m && pos2 <= r ) {
        if ( mas[pos1] <= mas[pos2] )
            buffer[posB++] = mas[pos1++];
        else
            buffer[posB++] = mas[pos2++];
    }
    while ( pos1 <= m )
        buffer[posB ++] = mas[pos1 ++];
    while ( pos2 <= r )
        buffer[posB ++] = mas[pos2 ++];
    std::copy( buffer.begin(), buffer.end(), (mas.begin() + l) );
}

void merge_sort( std::vector<int> &mas, int l, int r )
{
    int m = ( l + r ) >> 1;
    if (l == r) return;
    merge_sort( mas, l, m );
    merge_sort( mas, (m + 1), r );
    merge( mas, l, m, r );
}

int binarySearch( std::vector<int>& a, int key, int left ,int right)
{
    while (!(left >= right))
    {
        int mid = left + (right - left) / 2;

        if (a[mid] == key)
            return mid;

        if (a[mid] > key)
            right = mid;
        else
            left = mid + 1;
    }
    return right;
}

void mergeK ( std::vector<int>&a, int k, size_t place )
{
    while ( place < a.size() )
    {
        std::swap( a[place], k );
        ++place;
    }
}

void quick_sort_three_parts ( std::vector<int>& a, int l, int r )
{
    int k;
    int v = a[r];
    if ( r <= l )
        return;
    int i = l - 1, j = r, p = l - 1, q = r;
    for ( ;; )
    {
        while ( a[++i] < v )
            ;
        while ( v < a[--j] )
            if ( j == l )
                break;
        if ( i >= j )
            break;
        std::swap ( a[i], a[j] );
        if ( a[i] == v )
        {
            p++;
            std::swap ( a[p], a[i] );
        }
        if ( v == a[j] )
        {
            q--;
            std::swap ( a[q], a[j] );
        }
    }
    std::swap ( a[i], a[r] );
    j = i - 1;
    i = i + 1;
    for ( k = l; k <= p; k++, j-- )
        std::swap ( a[k], a[j] );
    for ( k = r - 1; k >= q; k--, i++ )
        std::swap ( a[k], a[i] );
    quick_sort_three_parts ( a, l, j );
    quick_sort_three_parts ( a, i, r );
}

int main()
{
    int64_t num;
    std::cin >> num;

    int numOut;
    std::cin >> numOut;
    std::vector <int> a (numOut, 0);

//    for ( int i = 0; i < num; ++i)
//    {
//        a[i] = num - i;
//    }

    for ( int i = 0; i < numOut ; ++i )
    {
        std::cin >> a[i];
    }

    quick_sort_three_parts( a, 0, numOut - 1 );

    int buf;
    for ( int i = numOut; i < num; ++i )
    {
        std::cin >> buf;
        if ( buf < a[numOut - 1] )
        {
//            for ( int i = 0; i < numOut; ++i)
//            {
//                std::cout << a[i] << " ";
//            }
//            std::cout << "\n ";
//3 7 4 5 6 1 15 4 2
              mergeK( a, buf, binarySearch(a, buf, 0, numOut ) ) ;
//            std::cout << " binarySearch(a, buf, 0, numOut ) = " << binarySearch(a, buf, 0, numOut ) << " \n";

        }
//        std::cout << buf << " ";
    }
//std::cout << " binarySearch(a, buf, 0, numOut ) = " << binarySearch(a, 15, 0, numOut ) << " \n";
    for ( int i = 0; i < numOut; ++i)
    {
        std::cout << a[i] << " ";
    }

    return 0;
}
