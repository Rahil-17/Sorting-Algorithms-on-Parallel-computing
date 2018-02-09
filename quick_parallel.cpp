#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int k=0;

int partition(vector<int> arr, int low, int high)
{
    int i, j, key;
    key = arr[low];
    i= low + 1;
    j= high;
    while(1)
    {
        while(i < high && key >= arr[i])
            i++;
        while(key < arr[j])
            j--;
    
        if(i < j)
            swap(arr[i],arr[j]);

        else
        {
            swap(arr[low],arr[j]);
            return(j);
        }
    }
}


void qsort(vector<int> arr, int low, int high)
{
    int j;
    if(low < high)
    {
        j = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                k=k+1;
                qsort(arr, low, j - 1);
            }

            #pragma omp section
            {
                k=k+1;
                qsort(arr, j + 1, high);
            }

        }
    }
}


int main()
{
    
    int n;
    cin>>n;
    vector<int> arr(n);
    
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    double start=omp_get_wtime();
    qsort(arr, 0, n - 1);
    double time=omp_get_wtime() - start;
    cout<<time<<endl;
} 