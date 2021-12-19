#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv)
{
	// Init MPI
	int rank, size, to_sent;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	int root_rank = 0;

	// Init array
	int *arr;
	if (rank == root_rank)
	{
		int vec_size = 1000000;
		arr = new int[vec_size]();
		for (int i = 0; i < vec_size; i++)
		{
			arr[i] = 1;
		}
		// Split arrays between processes as equally as possbile
		to_sent = vec_size / size;
	}

	// Send and receive size of transfering array
	MPI_Bcast(&to_sent, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
	// Allocate space for part of array A and B
	int *arr_part = new int[to_sent]();
	// Send and receive part of array A and B
	MPI_Scatter(arr, to_sent, MPI_INT, arr_part, to_sent, MPI_INT, root_rank, MPI_COMM_WORLD);

	// Main routine
	int s = 0, s_final;
	for (int i = 0; i < to_sent; i++) s += arr_part[i];

	// Merging answers
	double start, end;
	if (rank == root_rank) 
	{

		start = MPI_Wtime();
	}
	MPI_Reduce(&s, &s_final, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);

	// Output answer
	if (rank == root_rank)
	{
		end = MPI_Wtime();
		printf("Root process #%d: final answer is : %d\n", rank, s);
		printf("Point to point asnwer merging took %.0f us\n", (end - start) * 1000000);
	}

	// Finalize MPI
	MPI_Finalize();
	return 0;
}