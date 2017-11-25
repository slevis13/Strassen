#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int** make_matrix (int dim)
{
	int** C = malloc(dim*sizeof(int*));
	for(int i = 0; i < dim; i++)
		C[i] = malloc(dim*sizeof(int));
	return C;
}

int** standard (int** A, int** B, int dim)
{
	int** C = make_matrix (dim);
	/* if(dim == 1)
		C[0][0] = A[0][0] * B[0][0]; */
	//else 
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			//C[i][j] = 0;
			int sum = 0;
			for(int k = 0; k < dim; k++)
			{
				//C[i][j] += A[i][k]*B[k][j];
				sum += A[i][k]*B[k][j];
			}
			C[i][j] = sum;
		}
		free(A[i]);
	}
	for(int i = 0; i < dim; i++)
    {
        free(B[i]);
    }
    free(A);
    free(B);
    
	return C;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("Run with: standard [dimension] matrices.txt\n");
        return 1;
    }
    int dim = atoi(argv[1]);
    const char* inputfile = argv[2];

	int** A = make_matrix(dim);
	int** B = make_matrix(dim);
	
	/* read file, store integers in A and B */
	
	FILE *fp;
	fp = fopen(inputfile, "r");
	if (fp == NULL){
        printf("Could not open file %s \n", inputfile);
        return 0;
    }
	
	char buf[sizeof(int)+1];
    
    int row = 0;
    int col = 0;
    while(row < dim)
    {
        char c;
        int i = 0;
        while((c=fgetc(fp)) != '\n')
        {
            buf[i] = c;
            i++;
        }
        A[row][col] = atoi(buf);
        col++;
        if(col == dim){
            row++;
            col = 0;
        }
    }
    
    row = 0;
    col= 0;
    while(row < dim)
    {
        char c = fgetc(fp);
        int i = 0;
        while((c != '\n') && (c != EOF))
        {
            buf[i] = c;
            i++;
            c = fgetc(fp);
        }
        B[row][col] = atoi(buf);
        col++;
        if(col == dim){
            row++;
            col = 0;
        }
    }
    
	int fclose(FILE *fp);
    
    clock_t begin = clock();
    
    int **stan = standard(A, B, dim);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("standard: %f \n", time_spent);
    
   /*  for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
        	if(i != j)
        		continue;
            printf("%i \n", stan[i][j]);
        }
    } */
    for (int i = 0; i < dim; i++)
    {
        free(stan[i]);
    }
    free(stan);
    
}