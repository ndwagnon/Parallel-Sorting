#!/bin/bash
module load openmpi
srun --mpi=pmi2 ./mpi_merge >mpi_merge.txt
