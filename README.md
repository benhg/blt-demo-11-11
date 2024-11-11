# MPI Demo for BLT

Launch mac:

`mpirun exe/pop_dynamics_mpi_mac`

Kill mac:

`killall -SIGINT pop_dynamics_mpi_mac`


Launch BLT:
`mpirun --hostfile hostfile.txt exe/mpi_blt `

Kill BLT:

`srun --nodes=4 killall -SIGINT mpi_blt`

