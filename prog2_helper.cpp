#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>

double measure_time(int A[][800], int B[][800], int C[][800], int number_threads)
{
	int size = 800;
	auto begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int k = 0; k < size; k++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
        	C[i][j] = 0;
        }
    }
    return elapsed.count() * 1e-3;
}


int main(int argc, char* argv[])
{
	int size = 800;
	int iteration_per_thread_number = 10;
    int A[800][800], B[800][800], C[800][800];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
            C[i][j] = 0;
        }

    double efficiency[10], time[10];
    time[0] = measure_time(A, B, C, 1);
    efficiency[0] = 1;
    printf("For %d threads elapsed time is %.0f microseconds, efficiency is %.3f\n", 1, time[0], efficiency[0]);

    for (int number_threads = 2; number_threads < 11; number_threads++)
    {
    	int temp = 0;
    	for (int j = 0; j < iteration_per_thread_number; j++)
    	{
    		temp += measure_time(A, B, C, number_threads);
    	}
    	time[number_threads - 1] = temp / iteration_per_thread_number;
    	efficiency[number_threads - 1] = time[0] / time[number_threads - 1];
    	printf("For %d threads elapsed time is %.0f microseconds, efficiency is %.3f\n", number_threads, time[number_threads - 1], efficiency[number_threads - 1]);
    }
    return 0;
}

