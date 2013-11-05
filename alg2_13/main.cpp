/*
 *        Name: main.cpp
 *  Created on: Nov 1, 2013
 *      Author: roland
 *   Copiright: 2013 All rights reserved
 */

/*
 * 1.3 Ломаная 2.
 * Задано N точек на плоскости. Указать (N-1)-звенную
 * несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
 * Предполагается, что никакие три точки не лежат на одной прямой.
 *
 * Стройте ломаную от точки, имеющей наименьшую координату x.
 * Если таких точек несколько, то используйте точку с наименьшей
 * координатой y. Точки на ломаной расположите в порядке
 * убывания углов лучей от начальной точки до всех остальных точек.
 *
 */

#include <iostream>
#include <cmath>

struct coordinates
{
    double x;
    double y;
    double angle;
};

void input ( struct coordinates*, size_t );
void output ( const struct coordinates*, size_t );
void getFirstCoordinate ( struct coordinates*, size_t );
void putAngles ( struct coordinates* , size_t);

void insertion_sort ( struct coordinates* a, size_t num )
{
    size_t i, j;
    for ( i = 1; i < num; ++i )
    {
        float tmp = a[i].angle;
        for ( j = i; j > 1 && tmp > a[j - 1].angle; --j )
            std::swap(a[j], a[j - 1]);
    }
}

int main()
{
    size_t num;
    std::cin >> num;
    struct coordinates lines [num];

    for ( size_t i = 0; i < num; i++ )
    {
        input (lines, i);
    }

    getFirstCoordinate( lines, num );
    putAngles( lines, num );
    insertion_sort( lines, num );

    output( lines, num );

    return 0;
}

void input ( struct coordinates* in, size_t i)
{
    std::cin >> in[i].x;
    std::cin >> in[i].y;
}

void output ( const struct coordinates* out, size_t num)
{
    for ( size_t i = 0; i < num; i++)
    {
        std::cout << out[i].x << " ";
        std::cout << out[i].y << "\n";
//        std::cout << out[i].angle << "\n";
    }
}

void getFirstCoordinate ( struct coordinates* in, size_t num)
{
    double tmp1 = in[0].x;
    double tmp2 = in[0].y;
    size_t j = 0;
    for ( size_t i = 0; i < num; ++i )
    {
        if ( ((in[i].x < tmp1)) || (in[i].x == tmp1 && in[i].y < tmp2) )
        {
            j = i;
            tmp1 = in[i].x;
            tmp2 = in[i].y;
        }
    }
    std::swap(in[0],in[j]);
}

void putAngles ( struct coordinates* in, size_t num)
{
    for ( size_t i = 1; i < num; i++)
    {
        if ( in[i].x == in[0].x )
            in[i].angle = 6.28;
        else
        {
            in[i].angle = atan( ( in[i].y - in[0].y ) / ( in[i].x - in[0].x ) );
        }
    }
}
