gcc -c -fPIC integerset.c -o integerset.o
gcc -shared -o integerset.so integerset.o
