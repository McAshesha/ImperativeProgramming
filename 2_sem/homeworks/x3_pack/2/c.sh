gcc -Izlib -Izlib/minizip -DUSE_CRYPT -c zlib/minizip/unzip.c zlib/minizip/ioapi.c
ar rcs libminizip.a unzip.o ioapi.o
gcc -Izlib -c zlib/*.c
ar rcs libz.a *.o
gcc -Izlib -Izlib/minizip test.c -L. -lz -lminizip -o checked_solution
