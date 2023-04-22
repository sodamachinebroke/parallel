There are custom header files, that the program uses. The commons.h has things that every module uses and prod.c is has the main() function. 
Backup.c contains most of the functions still embedded into the main()'s file and should be ignored.
omp.c contains the functions that use OpenMP in any way.
pos.c has the POSIX thread using functions.
rec.c has recursive functions.
seq.c has the sequential calculation.

Autorun is set to create two files and then run the one witout an extension as it is made on linux. The other one is an .exe extension made for windows.
