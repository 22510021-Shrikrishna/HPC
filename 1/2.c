#include <stdio.h>
#include <omp.h>


int main(){

    int n;

    printf("Type number of threads = ");
    scanf("%d", &n);

    omp_set_num_threads(n);
    
    printf("Normal Sequential printing. \n");
    for(int i=0; i<n; i++){
        printf("Hello, World!\n");
    }    

    printf("Parallel Printing......\n");
    #pragma omp parallel
    {
        printf("Hello World... from thread = %d\n",
            omp_get_thread_num());
    }

    return 0;
}