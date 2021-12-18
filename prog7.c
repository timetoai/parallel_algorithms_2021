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
	int root_rank = size - 1;

	// Init arrays
	int *A, *B;
	if (rank == root_rank)
	{
		int vec_size = 1000000;
		A = new int[vec_size]();
		B = new int[vec_size]();
		for (int i = 0; i < vec_size; i++)
		{
			A[i] = 1;
			B[i] = 1;
		}
		// Split arrays between processes as equally as possbile
		to_sent = vec_size / size;
	}

	// Send and receive size of transfering array
	MPI_Bcast(&to_sent, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
	// Allocate space for part of array A and B
	int *A_part = new int[to_sent]();
	int *B_part = new int[to_sent]();
	// Send and receive part of array A and B
	MPI_Scatter(A, to_sent, MPI_INT, A_part, to_sent, MPI_INT, root_rank, MPI_COMM_WORLD);
	MPI_Scatter(B, to_sent, MPI_INT, B_part, to_sent, MPI_INT, root_rank, MPI_COMM_WORLD);

	// Main routine
	int sum = 0;
	for (int i = 0; i < to_sent; i++)
	{
		sum += A_part[i] * B_part[i];
	}

	// Gather sum in root process and output result
	int global_sum;
	MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);
	if (rank == root_rank)
		cout << "Root process with rank " << rank << ": local sum = " << sum  << " resulting sum = " << global_sum << endl;
	else
		cout << "Process with rank " << rank << ": local sum = " << sum  << endl;

	// Finalize MPI
	MPI_Finalize();
	return 0;
}