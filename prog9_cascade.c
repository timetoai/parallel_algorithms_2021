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
	int s = 0;
	for (int i = 0; i < to_sent; i++) s += arr_part[i];

	// Merging answers
	double start, end;
	if (rank == root_rank) start = MPI_Wtime();
	for (int reduce_order = 2; reduce_order <= size; reduce_order *= 2)
	{
		// Processes, which rank has non zero reminder when divided by reduce order, sends info to process,\
		// which rank is the result of integer division
		if (rank % reduce_order == 0)
		{
			if (rank + reduce_order / 2 < size) // check if need to receive
			{
				int temp;
				MPI_Recv(&temp, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				s += temp;
				printf("Reduce order %d, Process #%d: received sum %d from #%d, total sum is %d\n", reduce_order, rank, temp, status.MPI_SOURCE, s);
			}
		}
		else
		{
			MPI_Send(&s, 1, MPI_INT, rank - (rank % reduce_order), 0, MPI_COMM_WORLD);
			break;
		}
	}

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