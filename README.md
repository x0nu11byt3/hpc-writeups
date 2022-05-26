## HPC  Writeups

### OpenMPI - Compilation and Execution
For more information, please consult the official documentation [OpenMPI](https://www.open-mpi.org/doc/)
```sh
# Install OpenMPI in operating systems based on ArchLinux
$ sudo pacman -S openmpi
# compile
$ mpicc -lm yourfile.c -o yourapp
# running
$ mpirun -np <numberproccess> yourapp
```

### CUDA - Compilation and Execution
You can read more in [CUDA](https://docs.nvidia.com/cuda/), [Installation guide](https://docs.nvidia.com/cuda/cuda-quick-start-guide/index.html)
```sh
# Install CUDA in operating systems based on ArchLinux
$ sudo pacman -S cuda
# compile
$ nvcc  yourfile.c -o yourapp
# running
$ ./yourapp
```
