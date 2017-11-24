# strassen-algorithm
An implementation of Strassen's algorithm. Efficiently multiplies matrices using a divide-and-conquer approach.

## Background

The aim of this project was to determine, experimentally, where to set the "breakpoint" of Strassen's algorithm -- i.e. when to switch from recursion to the standard method of multiplication.

## Usage

The main program is at "strassen.c". "standard.c" is an implementation of the standard matrix multiplication algorithm. "matrix_gen.c" generates a text file of pseudo-random 1's and 0's, which acts as the matrices for our multiplication algorithms. Each run of matrix_gen generates a new set of matrices and overwrites any previous matrices generated.

To test it out for yourself: clone the repository, navigate to the appropriate directory, and run [make] in the terminal. 

First, to generate test matrices, run matrix_gen with the command: ./matrix_gen [dimension]. 

This will create a new text file called "matrices.txt", which will save to the project directory. You may make the dimension as small or as large as you'd like. Remember that, for example, a dimension of "1000" (i.e. 1000x1000) will generate two matrices of 1,000,000 values each; past this point, the matrices soon become too large to multiply quickly. 

To run standard, use the command: ./standard [dimension] matrices.txt. 

The dimension must match the dimension used for the most recent run of matrix_gen -- for example, if you have most recently run matrix_gen with dimension 1000, you must use 1000 as the dimension in strassen and standard. "matrices.txt" in the run command ought to be left as-is (it is the name of the text file we are using).

To run strassen, use: ./strassen [breakpoint] [dimension] matrices.txt. 

The "breakpoint" is the point below which the algorithm stops recursing and switches to the standard algorithm. For example, if the breakpoint is 50, the algorithm will keep dividing submatrices until their dimensions are less than 50x50, at which point it will "conquer" these small submatrices with standard multiplication. The breakpoint is, in other words, the line between recursion and the base case.

When standard and strassen halt, they will output their respective times taken.

## Discussion

Interestingly, when running strassen, it is not the case that a breakpoint of 1 (the simplest base case) provides the fastest solution. In fact, a breakpoint between 70 and 100 was found to be most efficient in the current implementation. While Strassen's algorithm has a lower worst-case time complexity than the standard algorithm, O(N^2.8074) vs O(N^3), in practice the standard method outperforms Strassen's for sufficiently small matrices. 

Feel free to try out different breakpoints for yourself! 

Also, notice how the gap between Strassen's and standard grows as the dimension of matrices grows. On my system, at dimension 2000, Strassen's (with a breakpoint of 70) outperforms the standard method by a factor of nearly 4!



