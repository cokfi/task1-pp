/* C program for estimation of Pi using Monte
   Carlo Simulation */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include <time.h>
#include <math.h>
int main(argc, argv)
int argc;
char** argv;
{
    int rank, size, done;
    long long int  d_inside, d_total, inside_tot, i, d_per_core;
    double x, y, pi, rad, starttime, endtime;;
    MPI_Init(&argc, &argv);
    starttime = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    d_inside = 0;
    d_total = 8064000000;
    d_per_core = d_total / (long long int)size;
    srand(time(NULL) + rank);
    pi = 0;
    done = 0;
        for (i = 0; i < d_per_core; i++) {
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            rad = x * x + y * y;
            if (rad <= 1) d_inside++;
            //printf("di is %d \n " ,d_inside);
        }
        MPI_Reduce(&d_inside, &inside_tot, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            //printf("in_tot is %lli \n " ,inside_tot);
            //printf("d_tot is %lli \n " ,d_total);
            pi = (double)inside_tot / (double)d_total * 4;
        }
            MPI_Bcast(&done, 2, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            printf("Pi is %0.9f \n ", pi);
            printf("Total iterations %lli \n", d_total);
            printf("Iterations per core %lli \n", d_per_core);
            endtime = MPI_Wtime();
            printf("The time taken is %f seconds\n", endtime - starttime);
        }
        MPI_Finalize();
        return 0;
    }