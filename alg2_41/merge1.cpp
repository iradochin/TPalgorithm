#include <iostream>
#include <vector>
#include <stdint.h>
#include <cstdio>

void outVector(std::vector<int>& a);  // Вывод значений
void merge( std::vector<int>&, int, int, int ); // Слияние упорядоченых множеств
void merge_sort( std::vector<int>&, int, int ); // Сортировка слиянием
void mergeK(std::vector<int>&, std::vector<int>&, int, int ); // Слияние 2 массивов до k 

int main() 
{    
    int64_t n, j = 0;  //n - количество значений
    scanf ("%ld", &n);

    int k, i;          // k - количество упорядоченных значений
    scanf ("%d", &k);
    
    std::vector<int> mas(k), buf(k);
    
    for(i = 0; i < k; ++ i)
        scanf ("%d",&mas[i]);
 
    merge_sort(mas, 0, k - 1);
   // outVector(mas);
   
    j = i;
    while(j < n) 
    {
        for (i = 0; i < k; ++ i, ++j) 
        {
            if (j >= n)
                break;
            scanf ("%d", &buf[i]);
        }
        
        merge_sort(buf, 0, i - 1);
        
        mergeK(mas, buf, k, i);
    }
    
    outVector(mas);
}

void outVector(std::vector<int> &a)
{
    size_t i;
    for ( i = 0; i < a.size(); ++ i)
        std::cout << a[i] << " ";
//    std::cout << std::endl;
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

void mergeK(std::vector<int>& one, std::vector<int>& two, int k, int i ) 
{
	// Слияние 2х упорядоченных векторов one и two в one
	// при помощи буфера длиной k
	
    std::vector<int> buffer(k);
    int pos1 = 0;
    int pos2 = 0;
    int posB = 0;
	
	// Слияние k элементов, или i , если элементов в two меньше k 
    while ( pos1 < k && pos2 < i && posB < k) 
    {
        if ( one[pos1] <= two[pos2] )
            buffer[posB++] = one[pos1++];
        else
            buffer[posB++] = two[pos2++];
    }
    
    // Если в two i элементов, дописываем в буфер из one 
    while ( pos1 < k && posB < k)
        buffer[posB ++] = one[pos1 ++];
    
	// Копируе буфер в исходный вектор с границами      
    std::copy( buffer.begin(), buffer.end(), one.begin() );
}
