gcc -c -o matrixsqr.o matrixsqr.c
gcc -c -o myblas.o myblas.c
gcc -c -o main.o main.c

gcc -o checked_solution main.o matrixsqr.o myblas.o -L. -lopenblas -pthread -Wl,-rpath=.
