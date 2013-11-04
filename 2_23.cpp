/*
 *        Name: main.cpp
 *  Created on: Nov 1, 2013
 *      Author: roland
 *	 Copiright: 2013 All rights reserved
 */

/*
  9
  0 3
  2 4
  5 8
  6 7
  9 11
  12 13
  14 16
  15 18
  17 20

  result = 17
 */

/*
 3
1 4
2 5
7 8
result = 5;
*/

/*
 8
 3 4
 5 6
 6 7
 1 4
 6 8
 0 4
 5 8
 2 2

 result = 7
 */
#include <iostream>

#include <algorithm>

struct coordinates
{
            int left;
            int right;
};

void swap ( struct coordinates&, struct coordinates& );
void input ( struct coordinates*, size_t );
void output (const struct coordinates*, size_t );
void quick_sort ( struct coordinates*, int );

int findSegment ( struct coordinates* line, size_t n )
{
    size_t i, k;
    int l,r;
    i=0;
    int result = 0;
    while (i<n)
    {
        l=line[i].left;
//        std::cout<<"l= "<<l<<" ";
        k=i;
        while (line[k].right>=line[i+1].left && i+1<n)
        {
            if (line[i+1].right<line[k].right)
            {
                i++;
            }
            else
            {
                i++;
                k=i;
            }
        }

        r=line[k].right;
//        std::cout<<"r= "<<r<<"\n";
        result+=r-l;
        i++;
    }
    return result;
}

int main ()
{
    int i;
    std::cin >> i;
    coordinates *line = new coordinates[i];
    input ( line, i );

    quick_sort(line, i);

//    output ( line, i );

    std::cout << findSegment( line, i )<<'\n';

    return 0;
}


void swap ( struct coordinates& one, struct coordinates& two )
{
    int temp;
    temp = one.left;
    one.left = two.left;
    two.left = temp;

    temp = one.right;
    one.right = two.right;
    two.right = temp;
}

void input ( struct coordinates *in, size_t n )
{
    for ( size_t i = 0; i < n; i++ )
    {
        std::cin >> in[i].left;
        std::cin >> in[i].right;
    }
}

void output (const struct coordinates *in, size_t n )
{
    for ( size_t i = 0; i < n; i++ )
    {
        std::cout << in[i].left;
        std::cout << " ";
        std::cout << in[i].right;
        std::cout << "\n";
    }
}

void quick_sort ( struct coordinates *a, int n )
{
    int i = 0;
    int j = n - 1;
    bool side = 0;
    while ( i != j )
    {
        if ( a[i].left > a[j].left )
        {
            swap ( a[i], a[j] );
            side = !side;
        }
        if ( side )
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
    if ( i > 1 )
        quick_sort ( a, i );
    if ( n > i + 1 )
        quick_sort ( a + (i + 1), n - (i + 1) );
}
