/*
 *        Name: test.cpp
 *  Created on: Nov 8, 2013
 *      Author: roland
 *	 Copiright: 2013 All rights reserved
 */

/*
 * 6 Быстрейшая сортировка.
 * Дан массив целых чисел в диапазоне [0..10^9].
 * Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов.
 * Все значения массива являются элементами псевдо-рандомной
 * последовательности. Необходимо отсортировать элементы массива за
 * минимально время и вывести каждый десятый элемент отсортированной
 * последовательности.
 * Минимальный набор оптимизаций, который необходимо реализовать:
 * 1. Оптимизация ввода/вывода
 * 2. Оптимизация выбора опорного элемента
 * 3. Оптимизация концевой рекурсии
 */

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <cstring>

// Быстрая сортировка
void insertion_sort (int*, int, int);
void quick_sort_three_parts (int*, int, int);

// LSD подсчетом
inline long digit (long, long);
void radix(int*, long, long);
void radixSort(int*, int);


int main(void)
{
//    struct timespec start, end;
//    clock_gettime (CLOCK_MONOTONIC, &start);
    int* a = (int*) malloc (25000000 * sizeof(int));
    srand(1);

    // Ввод по десять чисел сразу до EOF.
    int i = 0;
    while(!feof(stdin))
    {
        scanf ("%d %d %d %d %d %d %d %d %d %d ",
                &a[i], &a[i+1], &a[i+2], &a[i+3], &a[i+4], &a[i+5],
                &a[i+6], &a[i+7], &a[i+8], &a[i+9]);
        i += 10;
    }

    // Быстрая сортировка с делением на три части.
    quick_sort_three_parts (a, 0, i - 1);
    // Вставки для окончательной отсортировки.
    insertion_sort (a, 0, i);

    // LCD сортировка подсчётом
//    radixSort(a, i);

    // Вывод всех элементов
//  for ( int j = 0; j < i; ++j )
//      printf ( "%d ", a[j] );

    // Вывод каждого 10го элемента массива
    int j = 9;
    while (j < i)
    {
        printf ("%d ", a[j]);
        j += 10;
    }

    free (a);

//    clock_gettime (CLOCK_MONOTONIC, &end);

//    double diff1;
//    diff1 = (end.tv_sec + end.tv_nsec / 1e9)
//            - (start.tv_sec + start.tv_nsec / 1e9);
//    printf ("\nВремя выполнения quick: %lf с.\n", diff1);

    return 0;
}


/* ====== "Быстрая" быстрая сортировка ====== */

void insertion_sort (int* a, int left, int right)
{
    // Сортировка для почти упорядоченной последовательности
    for (int i = left; i < right; ++i)
    {
        int temp = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

void quick_sort_three_parts (int* a, int l, int r)
{
    // Быстрая сортировка с разделением на три части, меньше опорного,
    // равные опорному и больше опорного, быстра на часто повторяющихся числах.

//    printf ("l = %d, r= %d \n", l, r);

    // Оптимизация концевой рекурсии
    if (r - l < 10)
    {
        return;
    }

    // Опорный элемент рандомом
    std::swap(a[rand()%(r - l + 1) + l], a[r]);
    int v = a[r];

    int i = l - 1, j = r, p = l - 1, q = r;
    for ( ; ; )
    {
        // Формируем последовательность, пока не пересекутся i и j,
        // где на [l, p] - элементы равные опорному, на [p, i] -
        // меньше опорного, на [j, q] - элементы больше опорного,
        // на [q, r] равные опорному, а во время выполнения на [i, j] те
        // элементы, которые еще не рассмотрены.
        while (a[++i] < v)
            ;
        while (v < a[--j] && i != j)
            ;
        if (i >= j)
            break;
        std::swap (a[i], a[j]);
        if (a[i] == v)
            std::swap (a[++p], a[i]);

        if (v == a[j])
            std::swap (a[--q], a[j]);
    }

    // Ставим опорный на его правильное место.
    std::swap (a[i], a[r]);
    j = i - 1;
    i = i + 1;

    // Формируем последовательность, где на [l, j] < опорного,
    // на [j, i] равные, на [i, r] > опорного.
    int k;
    for (k = l; k <= p; ++k, --j)
        std::swap (a[k], a[j]);
    for (k = r - 1; k >= q; --k, ++i)
        std::swap (a[k], a[i]);

    // Сортируем неотсортированные половины, без элементов равных опорному.
    quick_sort_three_parts (a, l, j);
    quick_sort_three_parts (a, i, r);
}
/* ===================================== */


/* ====== LSD сортировка ====== */
inline long digit (long number, long d)
{
    // Функция достает dй байт числа
    return (number >> (8 * d)) & 0xFF;
}

void radix(int* a, long d, long num)
{
    // Сортировка подсчетом.

    // Массив, где индекс должен равняься числу.
    long* count = new long [257];

    // Формируем количество повторений числа.
    for(long i = 0; i < num; ++i)
        count[digit(a[i], d) + 1]++;

    // Формируем позиции элементов.
    for(long i = 2; i < 257; ++i)
        count[i] += count[i - 1];

    // Заносим отсортированную последовательность в массив.
    int* aCopy = new int [num];
    for(long i = 0; i < num; ++i)
        aCopy[count[digit(a[i], d)]++] = a[i];
    std::copy(aCopy, aCopy + num, a);
}

void radixSort(int* a, int num)
{
    for(int i = 0 ; i < 8; ++i)
    {
        // Для каждого байта
        radix(a, i, num);
    }
}
/* ===================================== */
