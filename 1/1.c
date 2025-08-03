#include <stdio.h>
#include <omp.h>


int main(void)
{
    #pragma omp parallel
    printf("Believe you can and you're halfway there. \n");
    return 0;
}
