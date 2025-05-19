gcc -shared -fPIC -o core.so state.c

# -shared: Produce a shared object which can be linked with other objects to form an executable.
# -fPIC: Generate position-independent code, suitable for dynamic linking.
# -o core.so: Output the shared library as core.so.
# state.c: The source file containing the State struct and function implementations.
