#include <stdio.h>
#include "mpi.h"
using namespace std;

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double rank_d = double(rank), message;
	int root_process = 4;

	if (rank == root_process)
	{
		cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_DOUBLE, MPI_ANY_SOURCE,
			         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			cout << "Hello from process " << message << " received by process " << rank << endl;
		}
	}
	else MPI_Send(&rank_d, 1, MPI_DOUBLE, root_process, 0, MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}