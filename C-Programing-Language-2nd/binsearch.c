#include <stdio.h>
#include <time.h>

#define SIZE 20000     
#define ITERATIONS 500000

int binsearch(int x, int v[], int n) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid]) 
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binsearch_opt(int x, int v[], int n) {
    int low = 0, high = n - 1, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return (x == v[low]) ? low : -1;
}

int main() {
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i * 2; 
    }

    clock_t start, end;
    double time_original, time_opt;

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < SIZE; j += 100) { 
            binsearch(j, arr, SIZE);
        }
    }
    end = clock();
    time_original = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        for (int j = 0; j < SIZE; j += 100) {
            binsearch_opt(j, arr, SIZE);
        }
    }
    end = clock();
    time_opt = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Original binsearch time:  %f seconds\n", time_original);
    printf("Optimized binsearch time: %f seconds\n", time_opt);
    printf("Difference:               %.2f%%\n", ((time_original - time_opt) / time_original) * 100);

    return 0;
}
