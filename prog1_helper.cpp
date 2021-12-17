#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>

int main_work(int argc, int size, int number_threads)
{
    int arr[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % INT_MAX;
        // std::cout << arr[i] << std::endl;
    }

    auto begin = std::chrono::high_resolution_clock::now();
    int max_val = 0;
#pragma omp parallel for reduction(max:max_val) num_threads(number_threads)
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    return elapsed.count() * 1e-3;
}

int main()
{
	int size = 2000000, iteration_per_thread = 100;
	int results[10];
	for (int nt = 1; nt < 11; nt++)
	{
		results[nt - 1] = 0;
		for (int j = 0; j < iteration_per_thread; j++)
		{
			results[nt - 1] += main_work(0, size, nt);
		}

		results[nt - 1] /= iteration_per_thread;
		printf("Using %d threads: elapsed time is %d microseconds \n", nt, results[nt - 1]);
	}
		
	return 0;
}