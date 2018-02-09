#include <omp.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

int m;

void bit_sort(int start, int length, vector<int>&input, int flag)
{
    int i;
    int mid_point;

    if (length == 1)
        return;

    mid_point = length / 2;

    // bitonic split
    for (i = start; i < start + mid_point; i++)
    {
        if (flag == 0)
        {
            if (input[i] > input[i + mid_point])
                swap(input[i], input[i + mid_point]);
        }
        else
        {
            if (input[i] < input[i + mid_point])
                swap(input[i], input[i + mid_point]);
        }
    }

    bit_sort(start, mid_point, input, flag);
    bit_sort(start + mid_point, mid_point, input, flag);
}

void bit_sort_para(int start, int length,vector<int>&input, int flag)
{
    int i;
    int mid_point;

    if (length == 1)
        return;

    mid_point = length / 2;

    // bitonic split
    #pragma omp parallel for shared(input, flag, start, mid_point) private(i)
    for (i = start; i < start + mid_point; i++)
    {
        if (flag == 0)
        {
            if (input[i] > input[i + mid_point])
                swap(input[i], input[i + mid_point]);
        }
        else
        {
            if (input[i] < input[i + mid_point])
                swap(input[i], input[i + mid_point]);
        }
    }

    if (mid_point > m)    // m is the size of sub part-> n/threads
    {
       
        bit_sort_para(start, mid_point, input, flag);
        bit_sort_para(start + mid_point, mid_point, input, flag);
    }

    return;
}

int main()
{
    int n;
    int flag,threads;
    cout<<"Input the length of a input(a power of 2): ";
    cin>>n;
    if (n % 2 !=0 )
    {
        cout<<"The length of a (sub)input is not divided by 2.\n";
        exit(0);
    }
    vector <int> input(n);
    
    for (int i = 0; i < n; i++)
    {
        cin>>input[i];
    }

    double start=omp_get_wtime();
    threads =  omp_get_max_threads();
    //printf("%d",threads);

    // making sure input is okay
    if ( n < threads * 2 )
    {
        cout<<"The size of the input is less than 2 * the number of processes.\n";
        exit(0);
    }

    
    m = n / threads; // the size of sub part
    int j;
    // make the input bitonic - part 1
    for (int i = 2; i <= m; i = 2 * i)
    {
        #pragma omp parallel for shared(i, input) private(j, flag)
        for (int j = 0; j < n; j += i)
        {
            if ((j / i) % 2 == 0)
                flag = 0;
            else
                flag = 1;
            bit_sort(j, i, input, flag);
        }
    }

    // make the input bitonic - part 2
    for (int i = 2; i <= threads; i = 2 * i)
    {
        for (int j = 0; j < threads; j += i)
        {
            if ((j / i) % 2 == 0)
                flag = 0;
            else
                flag = 1;
            bit_sort_para(j*m, i*m, input, flag);
        }
        
        #pragma omp parallel for shared(j)
        for (int j = 0; j < threads; j++)
        {
            if (j < i)
                flag = 0;
            else
                flag = 1;
            bit_sort(j*m, m, input, flag);
        }
    }

    double time=omp_get_wtime() - start;
    cout<<time<<endl;
    return 0;
}


