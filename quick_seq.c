#include<stdio.h>
#include<time.h>
#include<omp.h> 
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
 
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}
 
int main()
{
    int n;
    scanf("%d",&n);
    printf("%d\n",n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);    
    double start=omp_get_wtime();
    quickSort(arr, 0, n-1);
    double time=omp_get_wtime() - start;
    //cout<<time<<endl;
 
    printf("fun() took %f seconds to execute \n", time);
    //printf("Sorted array: n");
    //printArray(arr, n);
    return 0;
}