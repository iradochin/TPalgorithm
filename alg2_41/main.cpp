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

int binarySearch( std::vector<int>&, int, int ,int );  // Бинарный поиск
void mergeK ( std::vector<int>&, int, size_t );     // Слияние массива с элементом
//void quick_sort_three_parts ( std::vector<int>&, int, int ); // Быстрая на три части
void quickSort(std::vector<int>&, int, int );   // Быстрая
//void merge( std::vector<int> &, int, int, int );   //Слияние
//void merge_sort( std::vector<int> &, int, int );   //Сортировка слиянием

int main()
{
    int64_t num;
    std::cin >> num;

    int numOut;
    std::cin >> numOut;
    std::vector <int> a (numOut, 0);

// Считываем первые к элементов, затем сортируем их
    for ( int i = 0; i < numOut ; ++i )
    {
        std::cin >> a[i];
    }

//    merge_sort ( a, 0, numOut - 1 )
//    quick_sort_three_parts( a, 0, numOut - 1 );
    quickSort( a, 0, numOut - 1 );

// Считываем по одному числу и вставляем его в правильное место 
// результирующего вектора
    int buf;
    for ( int i = numOut; i < num; ++i )
    {
        std::cin >> buf;
        if ( buf < a[numOut - 1] )
            mergeK( a, buf, binarySearch(a, buf, 0, numOut ) ) ;
    }

    for ( int i = 0; i < numOut; ++i)
    {
        std::cout << a[i] << " ";
    }

    return 0;
}

void mergeK ( std::vector<int>&a, int k, size_t place )
{	
	// Вставка элемента k (без изменения упорядоченности) 
	// на место place в векторе a
    while ( place < a.size() )
    {
        std::swap( a[place], k );
        ++place;
    }
}

int binarySearch( std::vector<int>& a, int key, int left ,int right)
{
    while ( left < right )
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

void quickSort(std::vector<int>& a, int l, int r)
{
    int x = a[l + (r - l) / 2];
    int i = l;
    int j = r;
    while(i <= j)
    {
        while(a[i] < x)
            i++;

        while(a[j] > x)
            j--;

        if(i <= j)
        {
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (i<r)
        quickSort(a, i, r);

    if (l<j)
        quickSort(a, l, j);
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

void merge( std::vector<int>& mas, int left, int mid, int right ) 
{
	// Слияние 2х чаcтей вектора mas [left, mid], [mid+1, right]
	// при помощи буфера длиной [0, right - left + 1]
	  
    std::vector<int> buffer( right - left + 1 );
    int pos1 = left;        
    int pos2 = mid + 1;
    int posB = 0;

	// Слияние пока одина из частей вектора не достигла конца.
    while ( pos1 <= mid && pos2 <= right ) 
    {
        if ( mas[pos1] <= mas[pos2] )
            buffer[posB++] = mas[pos1++];
        else
            buffer[posB++] = mas[pos2++];
    }
    
    // Если одна из последовательностей не достигла конца, просто дописываем
    // елементы в конец.
    while ( pos1 <= mid )
        buffer[posB ++] = mas[pos1 ++];
    
    while ( pos2 <= right )
        buffer[posB ++] = mas[pos2 ++];
    
    // Копируе буфер в исходный вектор с границами [left, right] 
    std::copy( buffer.begin(), buffer.end(), (mas.begin() + left) );
}

void merge_sort( std::vector<int>& mas, int left, int right ) 
{
    if (left == right)                    // Если элементов для сортировки
		return;							  // нет.
		
	int mid = ( left + right ) / 2;
       
    merge_sort( mas, left, mid );         // Сортировка для левой половины
    merge_sort( mas, (mid + 1), right );  // Для правой
    merge( mas, left, mid, right );       // Их слияние
}
