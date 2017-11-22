# strassen-algorithm
An implementation of Strassen's algorithm. Efficiently multiplies matrices using a recursive, divide-and-conquer approach.

The main program is at "strassen.c". "standard.c" is an implementation of the standard matrix multiplication algorithm. "matrix_gen.c" generates a text file of randomly chosen 1's and 0's, which acts as the matrices for our multiplication algorithms. Each run of matrix_gen generates a new set of matrices and overwrites any previous matrices generated.

To test out the algorithm for yourself, you will need to clone the respository and compile each of the three C programs. 

Then, to generate test matrices, run matrix_gen with the command: ./matrix_gen [dimension]. This will create a new text file called "matrices.txt", which will save to the project directory. You may make the dimension as small or as large as you'd like. Remember that, for example, a dimension of 1000 will generate two matrices of 1,000,000 values each; past this point, the matrices soon become cumbersome to multiply. 

To run strassen and standard, use the command: ./[algorithm] [dimension] matrices.txt. The dimension must match the dimension used for the most recent run of matrix_gen -- for example, if you have most recently run matrix_gen with dimension 1000, you must use 1000 as the dimension in strassen and standard. "matrices.txt" in the run command ought to be left as-is (it is the name of the text file we are using).

Each iteration of strassen and standard will multiply the matrices and print the time taken (in seconds) to the console. 
