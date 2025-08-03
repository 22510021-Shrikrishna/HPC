#include <stdio.h>
#include <omp.h>

int main() {
    printf("1 Billion Slices \n");
    long num_slices = 1000000000;      // Number of rectangles
    double width = 1.0 / (double)num_slices;  // Width of each rectangle
    double sum = 0.0;
    double pi;
    int i;
    double height;

    #pragma omp parallel for reduction(+:sum) private(height)
    for (i = 0; i < num_slices; i++) {
        double midpoint = (i + 0.5) * width;       // Midpoint of current rectangle
        height = 4.0 / (1.0 + midpoint * midpoint);  // Height of rectangle at midpoint
        sum += height;
    }

    pi = width * sum;  // Area approximation = width * sum of heights

    printf("Calculated Pi = %.15lf\n", pi);

    return 0;
}