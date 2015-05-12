#include "mc_parallel_vars.h"
void print_game_stats(void){
	int mpi_comm_size;
	int mpi_rank;
	int game_counts[3];
	
	game_counts[0]=total_game_count_mc_original;
	game_counts[1]=total_game_count_mc_omp;
	game_counts[2]=total_game_count_mc_mpi;	

	MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&mpi_comm_size);

	if(mpi_rank==0 && mpi_comm_size == 1){
		if(total_game_count_mc_original!=0){
			printf("Monte-Carlo original total games: %d\n", total_game_count_mc_original);
		}
		if(total_game_count_mc_omp!=0){
			printf("Monte-Carlo OMP total games: %d\n", total_game_count_mc_omp);
		}
		if(total_game_count_mc_mpi!=0){
			printf("Monte-Carlo MPI total games: %d\n", total_game_count_mc_mpi);
		}
	}
	else if(mpi_rank==0 && mpi_comm_size > 1){
		int game_counts_buffer[3];
		MPI_Reduce(&game_counts[0], &game_counts_buffer[0], 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		if(game_counts[0]!=0){
			printf("Monte-Carlo original total games: %d\n", game_counts_buffer[0]);
		}
		if(game_counts[1]!=0){
			printf("Monte-Carlo OMP total games: %d\n", game_counts_buffer[1]);
		}
		if(game_counts[2]!=0){
			printf("Monte-Carlo MPI total games: %d\n", game_counts_buffer[2]);
		}
	}
	else if(mpi_rank>0){
		MPI_Reduce(&game_counts[0], NULL, 3, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	total_game_count_mc_original = 0;
	total_game_count_mc_omp = 0;
	total_game_count_mc_mpi = 0;
	return;
}
