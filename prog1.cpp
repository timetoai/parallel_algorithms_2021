#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>


int main(int argc, char* argv[])
{
    int size = atoi(argv[1]);
    int number_threads = atoi(argv[2]);
    int arr[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % INT_MAX;
        // std::cout << arr[i] << std::endl;
    }

    auto begin = std::chrono::high_resolution_clock::now();
    int max_val = 0;
#pragma omp parallel for num_threads(number_threads) shared(arr) reduction(max:max_val)
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Maximum value: %d\n\n", max_val);
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %.5f seconds\n", elapsed.count() * 1e-9);
    return 0;
}