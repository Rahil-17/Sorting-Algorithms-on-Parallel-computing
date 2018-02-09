#include <omp.h>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
int n;
void odd_even(vector <int>&arr)
{
    int flag=1;
    while(flag)
    {
        #pragma omp parallel// private(tmp)
        {
                flag = 0;
               
                #pragma omp for \
                        reduction(+:flag)
                for(int i = 0; i < n - 1; i = i + 2)
                {
                        if(arr[i] > arr[i+1] )
                        {
                            swap(arr[i],arr[i+1]);
                            ++flag;
                        }
                }
                #pragma omp for \
                        reduction(+:flag)
                for(int i = 1; i < n - 1; i = i + 2)
                {
                        if( arr[i] > arr[i+1] )
                        {
                            swap(arr[i],arr[i+1]);
                            ++flag;
                        }
                }
        }
    }
}
int main()
{
    int i;
    cin>>n;
    vector<int>arr(n);
       
    for(i = 0; i < n; ++i)
        cin>>arr[i];
    double start=omp_get_wtime();
    odd_even(arr);
	double time=omp_get_wtime() - start;
    cout<<time<<endl;
    //printf("sorted");
	// for(i = 0; i < n; ++i)
      //  cout<<arr[i]<<" ";

    return 0;

}
