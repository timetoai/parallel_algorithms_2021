#include <iostream>
#include <mpi.h>
using namespace std;

void send_int_arr(int src, int dest, int size, int *arr, MPI_Status status, int n_times)
{
	int L = size * sizeof(int);
	double start, end, T, R, s;

	start = MPI_Wtime();
	for (int i = 0; i < n_times; i++)
		MPI_Send(arr, size, MPI_INT, dest, 0, MPI_COMM_WORLD);
	end = MPI_Wtime();

	T = (end - start) / n_times * 1000000;  // in us
	R = 2 * L / T / 1024 / 1024;  // in MB/s
	s = T / 2; // in us

	printf("Process with rank %d: message_size = %7d, avg send time = %4.0f [us], bandwidth = %.3f [MB/s], latency = %4.0f [us]\n", src, size, T, R, s);
}

void recv_int_arr(int src, int dest, int size, int *arr, MPI_Status status, int n_times)
{
	int L = size * sizeof(int);
	double start, end, T, R, s;
			
	start = MPI_Wtime();
	for (int i = 0; i < 10; i++)
		MPI_Recv(arr, size, MPI_INT, dest, 0, MPI_COMM_WORLD, &status);
	end = MPI_Wtime();

	T = (end - start) / n_times * 1000000; // in us
	R = 2 * L / T / 1024 / 1024; // in MB/s
	s = T / 2; // in us

	printf("Process with rank %d: message_size = %7d, avg recv time = %4.0f [us], bandwidth = %.3f [MB/s], latency = %4.0f [us]\n", src, size, T, R, s);
}

int main(int argc, char **argv)
{
	// Init MPI
	int rank, size, n_times = 10;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int *arr;

	for (int message_size = 1; message_size <= 1000000; message_size *= 10)
	{
		arr = new int[message_size]();
		if (rank == 0)
		{
			for (int i = 0; i < message_size; i++) arr[i] = 1;

			send_int_arr(rank, rank ^ 1, message_size, arr, status, n_times);

			recv_int_arr(rank, rank ^ 1, message_size, arr, status, n_times);
		}
		else if (rank == 1)
		{
			recv_int_arr(rank, rank ^ 1, message_size, arr, status, n_times);

			send_int_arr(rank, rank ^ 1, message_size, arr, status, n_times);
		}
		delete arr;
	}

	// Finalize MPI
	MPI_Finalize();
	return 0;
}