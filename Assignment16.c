#include "mpi.h"
int main(int argc, char **argv)
{
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int root_rank = 0;

	if (root_rank == rank) printf("Setting color to (rank %% 2)\n");
	MPI_Comm_split(MPI_COMM_WORLD, rank % 2, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	//Display rank and rank1
	printf("rank = %d, rank1 = %d\n", rank, rank1);
	MPI_Comm_free(&comm_revs);
	MPI_Barrier(MPI_COMM_WORLD);

	if (root_rank == rank) printf("Setting color to (rank %% 3)\n");
	MPI_Comm_split(MPI_COMM_WORLD, rank % 3, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	//Display rank and rank1
	printf("rank = %d, rank1 = %d\n", rank, rank1);
	MPI_Comm_free(&comm_revs);

	MPI_Finalize();
}