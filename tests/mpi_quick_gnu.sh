#!/bin/bash
module load openmpi
srun --mpi=pmi2 ./mpi_quick >mpi_quick.txt
