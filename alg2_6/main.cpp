#include <stdio.h>
#include <time.h>
#include <algorithm>

#define ITEMS 1000000
/* ====== Вставки ====== */

void insertion (int *a, int l, int r)
{
    int i;
    for ( i = r; i > l; --i )
        std::swap ( a [i-1] , a[i] );
    for ( i = l+2; i <= r; ++i )
    {
        int j = i;
        int v = a[i];
        while (v < a[j-1])
        {
            a[j] = a[j-1];
            --j;
        }
        a[j] = v;
    }
}

/* ===================================== */

/* ====== Быстрая на три части сортировка====== */
void medianOfThree (int* a, int left, int right)
{
    // Установка элементов с индексами left, right, ( left + right ) / 2
    // В порядке [средний, минимальный, максимальный] на позиции
    // [left, ( left + right ) / 2, right]

    if ( a[( left + right ) / 2] > a[right] )
        std::swap ( a[( left + right ) / 2], a[right] );
    if ( a[left] < a[( left + right ) / 2] )
        std::swap ( a[left], a[( left + right ) / 2] );
    if ( a[left] > a[right] )
        std::swap ( a[left], a[right] );
}

void quick_sort_three_parts ( int *a, int l, int r )
{
    if ( r - l < 12 )
    {
        insertion (a,l,r);
        return;
    }
    int k;
    medianOfThree(a, l, r);
//    int v = a[rand()%( r - l + 1) + l];
    int v = a[l];
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

/* ===================================== */

/* ====== Пирамидальная сортировка ====== */
void heap_pop ( int *a, int n )
{
    std::swap ( a[n], a[1] );
    for ( int i = 1; 2 * i < n; )
    {
        i *= 2;
        if ( i + 1 < n && a[i] < a[i + 1] )
        {
            i += 1;
        }
        if ( a[i / 2] < a[i] )
        {
            std::swap ( a[i / 2], a[i] );
        }
    }
}

void heap_make ( int *a, int n )
{
    for ( int i = n / 2; i >= 1; --i )
    {
        for ( int j = i; j <= n / 2; )
        {
            int k = j * 2;
            if ( (k + 1 <= n) && (a[k] < a[k + 1]) )
            {
                ++k;
            }
            if ( a[j] < a[k] )
            {
                std::swap ( a[k], a[j] );
                j = k;
            }
            else
            {
                break;
            }
        }
    }
}

void heap_sort_fast ( int *data, int n )
{
    heap_make ( data - 1, n );
    for ( int i = 0; i < n; ++i )
    {
        heap_pop ( data - 1, n - i );
    }
}
/* ===================================== */

/* ====== BinaryQuick MSD сортировка ====== */
inline int bit ( long long number, int d )
{
    return (number >> d) & 1;
}

void quicksortBin( int* a, int l, int r, int d )
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
/* ===================================== */

/* ====== Слиянием сортировка ====== */
void merge( int* mas, int left, int mid, int right )
{
    // Слияние 2х чаcтей вектора mas [left, mid], [mid+1, right]
    // при помощи буфера длиной [0, right - left + 1]

    int* buffer = new int[ right - left + 1 ];
    int pos1 = left;
    int pos2 = mid + 1;
    int posB = 0;
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
    std::copy( buffer, buffer + right - left +1, mas + left );
}

void merge_sort( int* mas, int left, int right )
{
    if ( right - left < 15 )
    {
        insertion (mas, left, right);
        return;
    }

    int mid = ( left + right ) / 2;

    merge_sort( mas, left, mid );         // Сортировка для левой половины
    merge_sort( mas, (mid + 1), right );  // Для правой
    merge( mas, left, mid, right );       // Их слияние
}
/* ===================================== */

/* ====== LSD сортировка ====== */
inline long digit (long number, long d)
{
    return (number >> (8 * d)) & 0xFF;
}

void radix(int* a, long d, long num)
{
    long n = num;
    long* count = new long [257];

    for(long i = 0; i < n; ++i)
        count[digit(a[i], d) + 1]++;

    for(long i = 2; i < 257; ++i)
        count[i] += count[i - 1];

    int* aCopy = new int [n];
    for(long i = 0; i < n; ++i)
        aCopy[count[digit(a[i], d)]++] = a[i];

    std::copy( aCopy, aCopy + n, a);
}

void radixSort(int* a, long num)
{
    for(long i = 0 ; i < 8; ++i)
    {
        radix(a, i, num);
    }
}
/* ===================================== */


int main(void)
{
    int i;
    struct timespec start, end;
    int a[1000000];
    double diff1, diff2, diff3, diff4, diff5;


    for ( i = 0; i < ITEMS; ++i )
        scanf ( "%d", &a[i]);
    clock_gettime ( CLOCK_MONOTONIC, &start );
    quick_sort_three_parts (a, 0, ITEMS - 1);
//    heap_sort_fast(a, 999999);
//    insertion( a, 0, 999999 );
//    quicksortBin(a, 0, 999999, 64);
//    merge_sort(a, 0, 999999);
//    radixSort(a, ITEMS);
    clock_gettime ( CLOCK_MONOTONIC, &end );

    diff1 = (end.tv_sec + end.tv_nsec / 1e9)
                - (start.tv_sec + start.tv_nsec / 1e9);
    printf ( "\nВремя выполнения quick: %lf с.\n", diff1 );

    for ( i = 0; i < ITEMS; ++i )
        scanf ( "%d", &a[i]);

    clock_gettime ( CLOCK_MONOTONIC, &start );
    heap_sort_fast(a, ITEMS - 1);
    clock_gettime ( CLOCK_MONOTONIC, &end );

    diff2 = (end.tv_sec + end.tv_nsec / 1e9)
                - (start.tv_sec + start.tv_nsec / 1e9);
    printf ( "\nВремя выполнения heap: %lf с.\n", diff2 );


    for ( i = 0; i < ITEMS; ++i )
        scanf ( "%d", &a[i]);

    clock_gettime ( CLOCK_MONOTONIC, &start );
    quicksortBin(a, 0, ITEMS - 1, 64);
    clock_gettime ( CLOCK_MONOTONIC, &end );

    diff3 = (end.tv_sec + end.tv_nsec / 1e9)
                - (start.tv_sec + start.tv_nsec / 1e9);
    printf ( "\nВремя выполнения quickbin: %lf с.\n", diff3 );


    for ( i = 0; i < ITEMS; ++i )
        scanf ( "%d", &a[i]);
    clock_gettime ( CLOCK_MONOTONIC, &start );
    merge_sort(a, 0, ITEMS - 1);
    clock_gettime ( CLOCK_MONOTONIC, &end );

    diff4 = (end.tv_sec + end.tv_nsec / 1e9)
                - (start.tv_sec + start.tv_nsec / 1e9);
    printf ( "\nВремя выполнения merge: %lf с.\n", diff4 );

    for ( i = 0; i < ITEMS; ++i )
        scanf ( "%d", &a[i]);
    clock_gettime ( CLOCK_MONOTONIC, &start );
    radixSort(a, ITEMS);
    clock_gettime ( CLOCK_MONOTONIC, &end );

    diff5 = (end.tv_sec + end.tv_nsec / 1e9)
                - (start.tv_sec + start.tv_nsec / 1e9);
    printf ( "\nВремя выполнения LSD: %lf с.\n", diff5 );

//        i = 10;
//        while ( i != 1000000 )
//        {
//            printf ( "%d ", a[i] );
//            i+=10;
//        }
        for ( i = 0; i < 10; ++i )
            printf ( "%d ", a[i] );

    return 0;
}

