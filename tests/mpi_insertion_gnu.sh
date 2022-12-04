#!/bin/bash
module load openmpi
srun --mpi=pmi2 ./mpi_insertion >mpi_insertion.txt
