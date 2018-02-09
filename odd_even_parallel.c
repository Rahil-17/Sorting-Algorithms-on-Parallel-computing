#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
        int i,n,tmp,changes;
        scanf("%d", &n);
        int arr[n];
        
        for(i = 0; i < n; ++i)
        {
			//printf("\nEnter no.");
            scanf("%d", &arr[i]);
        }    
    changes = 1;
    while(changes)
    {
    #pragma omp parallel private(tmp)
    {
            changes = 0;
           
            #pragma omp for \
                    reduction(+:changes)
            for(i = 0; i < n - 1; i = i + 2)
            {
                    if(arr[i] > arr[i+1] )
                    {
                            tmp = arr[i];
                            arr[i] = arr[i+1];
                            arr[i+1] = tmp;
                            ++changes;
                    }
            }
            #pragma omp for \
                    reduction(+:changes)
            for(i = 1; i < n - 1; i = i + 2)
            {
                    if( arr[i] > arr[i+1] )
                    {
                            tmp = arr[i];
                            arr[i] = arr[i+1];
                            arr[i+1] = tmp;
                            ++changes;
                    }
            }
    }
    }
	printf("sorted");
	 //for(i = 0; i < n; ++i)
       //     printf("%d ",arr[i]);
    return 0;

}
