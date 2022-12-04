#!/bin/bash
module load openmpi
srun --mpi=pmi2 ./merge_gnu
