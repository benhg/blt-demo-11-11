# MPI Demo for BLT

Launch with graphics:

`exe/pop_dynamics_graphics`

Launch mac:

`mpirun exe/pop_dynamics_mpi_mac`

Kill mac:

`killall -SIGINT pop_dynamics_mpi_mac`


Launch BLT:

`mpirun --hostfile mpi_hostfile --use-hwthread-cpus exe/pop_dynamics_mpi_blt`

Kill BLT:

`srun --nodes=4 killall -SIGINT pop_dynamics_mpi_blt`


Launch homelab:

`mpirun --use-hwthread-cpus pop_dynamics_linux `

Kill homelab:

`killall -SIGINT pop_dynamics_linux`
