#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

// 1 means ascending
// 0 means descending

void swapper(int a[],int i,int j,int sort_way)
{
  if(sort_way==0 && a[i]<a[j])
  	swap(a[i],a[j]);

  if(sort_way==1 && a[i]>a[j])
  	swap(a[i],a[j]);

}

void b_merge(int a[],int left,int right,int sort_way)
{
	if(right>1)
	{
		int mid=right/2;
		for(int i=left;i<left+mid;i++)
			swapper(a,i,i+mid,sort_way);

		b_merge(a , left , mid , sort_way);
		b_merge(a , left + mid , mid , sort_way);
	}	
}

void b_sort(int a[],int left,int right,int sort_way)
{
	if(right>1)
	{
		int mid=right/2;
		b_sort(a,left,mid,1);
		b_sort(a,left+mid,mid,0);
		b_merge(a,left,right,sort_way);
	}	
}

void call_bsort(int a[],int n,int sort_way)
	{b_sort(a,0,n,sort_way);}

int main()
{
	int n;
	cin>>n;
	int arr[n];
	cout<<n<<endl;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	double start=omp_get_wtime();
	call_bsort(arr,n,1);
	double time=omp_get_wtime() - start;
    cout<<time<<endl;
	//for(int i=0;i<n;i++)
	//	cout<<arr[i]<<" ";
	return 0;
}	
