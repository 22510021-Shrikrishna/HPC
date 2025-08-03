#include <iostream>
#include <vector>
#include <algorithm>  // for sort
#include <omp.h>      // for OpenMP

using namespace std;

int main() {
    // Example vectors
    vector<int> a = {3, 9, 6};
    vector<int> b = {5, 21, 11};
    
    int n = a.size();

    // Sort a ascending
    sort(a.begin(), a.end());

    // Sort b descending
    sort(b.begin(), b.end(), greater<int>());

    // Calculate minimum scalar product in parallel
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }

    cout << "First array is ";
    for(int i: a){
        cout << i << " ";
    }
    cout << endl;

    cout << "Second array is ";
    for(int i: b){
        cout << i << " ";
    }
    cout << endl;
    cout << "Minimum Scalar Product: " << result << endl;

    return 0;
}
