#include <stdio.h>
#include <omp.h>


int main(){

    int n;
    printf("Enter desired number of threads \n");
    scanf("%d", &n);

    int arr1[5] = {3, 6, 9, 11, 21};
    int arr2[5] = {21, 11, 9, 6, 3};
    int res[5];

    omp_set_num_threads(n);

    #pragma omp parallel for
    for(int i=0; i<5; i++){
        res[i] = arr1[i] + arr2[i];
        printf(" addition of %dth elements is done by thread number %d \n", i, omp_get_thread_num()); 
    }

    
    printf(" Result array is " ); 

    for(int i=0; i<5; i++){
        printf("%d ", res[i]);
    }
}