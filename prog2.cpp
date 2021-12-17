#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>


int main(int argc, char* argv[])
{
    int size = atoi(argv[1]);
    int number_threads = atoi(argv[2]);
    int A[size][size], B[size][size], C[size][size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
            C[i][j] = 0;
        }

    auto begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is ijk\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int i = 0; i < size; i++)
    {
        for (int k = 0; k < size; k++)
        {
            for (int j = 0; j < size; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is ikj\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            for (int k = 0; k < size; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is jik\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int j = 0; j < size; j++)
    {
        for (int k = 0; k < size; k++)
        {
            for (int i = 0; i < size; i++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is jki\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    begin = std::chrono::high_resolution_clock::now();
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
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is kij\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(number_threads) shared(A,B,C) collapse(3)
    for (int k = 0; k < size; k++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int i = 0; i < size; i++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    printf("Order is kji\n");
    printf("Size of array: %d elements\n", size);
    printf("Number of threads used: %d\n", number_threads);
    printf("Time measured: %d microseconds\n\n", int(elapsed.count() * 1e-3));

    if (size == 5)
    {
        printf("\nA matrix:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d\t", A[i][j]);
            }
            printf("\n");
        }
        printf("\nB matrix:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d\t", B[i][j]);
            }
            printf("\n");
        }
        printf("\nC matrix:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%d\t", C[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}