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

// standard algorithm
int** standard (int** A, int** B, int dim)
{
	int** C = make_matrix (dim);
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
		{
			int sum = 0;
			for(int k = 0; k < dim; k++)
			{
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

// control flow for recursion

int** strassen (int** A, int** B, int dim);

int** multiply (int** A, int** B, int dim)
{
    int** C = NULL;
	if(dim <= 70)
	{
	    C = standard(A, B, dim);
	}
	else
	    C = strassen(A, B, dim);

	return C;
}

// strassen divide + conquer
int** c00 (int** A, int** B, int** p2, int** p4, int** p5, int dim)
{
    int sub_dim = dim/2;
	
	int** b_d = make_matrix(sub_dim);
	int** g_h = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			b_d[i][j] = A[i][j+sub_dim] - A[i+sub_dim][j+sub_dim];
		}
	}
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			g_h[i][j] = B[i+sub_dim][j] + B[i+sub_dim][j+sub_dim];
		}
	}

	int** p6 = multiply(b_d, g_h, sub_dim);
	
	int** subtract = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			subtract[i][j] = p4[i][j] - p2[i][j];
		}
	}
	int** add1 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			add1[i][j] = p6[i][j] + subtract[i][j];
		}
		free(subtract[i]);
	}
	free(subtract);
	int** c00 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			c00[i][j] = p5[i][j] + add1[i][j];
		}
		free(add1[i]);
	}
	free(add1);
	for(int i = 0; i < sub_dim; i ++)
	{
		free(p6[i]);
	}
	free(p6);
	
	return c00;
}
int** c01 (int** p1, int** p2, int dim)
{
    int sub_dim = dim/2;
	
	int** c01 = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i++)
	{
		for(int j = 0; j < sub_dim; j++)
			c01[i][j] = p1[i][j] + p2[i][j];
	}
	return c01;
}
int** c02 (int** p3, int** p4, int dim)
{
	int sub_dim = dim/2;
	
	int** c02 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			c02[i][j] = p3[i][j] + p4[i][j];
		}
	}
	return c02;
}
int** c03 (int** A, int** B, int** p1, int** p3, int** p5, int dim)
{
	int sub_dim = dim/2;
	
	int** e_f = make_matrix(sub_dim);
	int** a_c = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			e_f[i][j] = B[i][j] + B[i][j+sub_dim];
		}
	}
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			a_c[i][j] = A[i][j] - A[i+sub_dim][j];
		}
	}

	int** p7 = multiply(a_c, e_f, sub_dim);
	
	int** subtract1 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			subtract1[i][j] = p1[i][j] - p3[i][j];
		}
	}
	int** subtract2 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			subtract2[i][j] = subtract1[i][j] - p7[i][j];
		}
		free(subtract1[i]);
	}
	free(subtract1);
	
	
	int** c03 = make_matrix(sub_dim);
	for (int i = 0; i < sub_dim; i++)
	{
		for (int j = 0; j < sub_dim; j++)
		{
			c03[i][j] = p5[i][j] + subtract2[i][j];
		}
		free(subtract2[i]);
	}
	free(subtract2);
	for(int i = 0; i < sub_dim; i++)
	{
		free(p7[i]);
	}
	free(p7);
	return c03;
}

// recursive terms to calculate submatrices
int** p1 (int** A, int** B, int dim)
{
	int sub_dim = dim/2;
	int** a = make_matrix(sub_dim);
	int** f_h = make_matrix(sub_dim);
	int** p1 = NULL;
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			a[i][j] = A[i][j];
			f_h[i][j] = B[i][j+sub_dim] - B[i+sub_dim][j+sub_dim];
		}
	}
	p1 = multiply(a, f_h, sub_dim);
	return p1;
}
int** p2 (int** A, int** B, int dim)
{
	int sub_dim = dim/2;
	int** a_b = make_matrix(sub_dim);
	int** h = make_matrix(sub_dim);
	int** p2 = NULL;
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			a_b[i][j] =  A[i][j] + A[i][j+sub_dim];
			h[i][j] = B[i+sub_dim][j+sub_dim];
		}
	}
	p2 = multiply(a_b, h, sub_dim);
	return p2;
}
int** p3 (int** A, int** B, int dim)
{
	int sub_dim = dim/2;
	int** p3 = NULL;
	int** c_d = make_matrix(sub_dim);
	int** e = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			c_d[i][j] = A[i+sub_dim][j] + A[i+sub_dim][j+sub_dim];
			e[i][j] = B[i][j];
		}
	}
	p3 = multiply(c_d, e, sub_dim);
	return p3;
}
int** p4 (int** A, int** B, int dim)
{
	int sub_dim = dim/2;
	int** p4 = NULL;
	int** d = make_matrix(sub_dim);
	int** g_e = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			g_e[i][j] = B[i+sub_dim][j] - B[i][j];
			d[i][j] = A[i+sub_dim][j+sub_dim];
		}
	}
	p4 = multiply(d, g_e, sub_dim);
	return p4;
}
int** p5 (int** A, int** B, int dim)
{
	int sub_dim = dim/2;
	int** p5 = NULL;
	int** e_h = make_matrix(sub_dim);
	int** a_d = make_matrix(sub_dim);
	for(int i = 0; i < sub_dim; i ++)
	{
		for(int j = 0; j < sub_dim; j++)
		{
			a_d[i][j] = A[i][j] + A[i+sub_dim][j+sub_dim];
			e_h[i][j] = B[i][j] + B[i+sub_dim][j+sub_dim];
		}
	}
	p5 = multiply(a_d, e_h, sub_dim);
	return p5;
}

// main function
int** strassen (int** A, int** B, int dim)
{
	int** C = NULL;

	int sub_dim = dim/2;
	if(dim % 2 == 0)
	{
		C = make_matrix(dim);
		int** p_1 = p1(A, B, dim);
		int** p_2 = p2(A, B, dim);
		int** p_3 = p3(A, B, dim);
		int** p_4 = p4(A, B, dim);
		int** p_5 = p5(A, B, dim);

		int** c_00 = c00(A, B, p_2, p_4, p_5, dim);
		int** c_01 = c01(p_1, p_2, dim);
		int** c_02 = c02(p_3, p_4, dim);
		int** c_03 = c03(A, B, p_1, p_3, p_5, dim);
		for(int i = 0; i < sub_dim; i++)
		{
			free(p_1[i]);
			free(p_2[i]);
			free(p_3[i]);
			free(p_4[i]);
			free(p_5[i]);
		}
		free(p_1);
		free(p_2);
		free(p_3);
		free(p_4);
		free(p_5);

		for(int i = 0; i < sub_dim; i++)
		{
		    for(int j = 0; j < sub_dim; j++)
		    {
		        C[i][j] = c_00[i][j];
		        C[i][j+sub_dim] = c_01[i][j];
		        C[i+sub_dim][j] = c_02[i][j];
		        C[i+sub_dim][j+sub_dim] = c_03[i][j];
		    }
		    free(c_00[i]);
		    free(c_01[i]);
		    free(c_02[i]);
		    free(c_03[i]);
		}
		free(c_00);
		free(c_01);
		free(c_02);
		free(c_03);
		
		for (int i = 0; i < dim; i++)
	    {
	        free(A[i]);
	        free(B[i]);
	    }
	    free(A);
	    free(B);
	}
	else
		// padding
	{
		int pad_dim = dim + 1;
		int** A_pad = make_matrix(pad_dim);
		int** B_pad = make_matrix(pad_dim);
		for(int i = 0; i < dim; i++)
		{
			for(int j = 0; j < dim; j++)
			{
				A_pad[i][j] = A[i][j];
				B_pad[i][j] = B[i][j];
			}
			A_pad[i][dim] = 0;
			B_pad[i][dim] = 0;
			free(A[i]);
			free(B[i]);
		}
		free(A);
		free(B);
		
		for(int j = 0; j < pad_dim; j++)
		{
			A_pad[dim][j] = 0;
			B_pad[dim][j] = 0;
		}

		C = make_matrix(dim);
		int** p_1 = p1(A_pad, B_pad, pad_dim);
		int** p_2 = p2(A_pad, B_pad, pad_dim);
		int** p_3 = p3(A_pad, B_pad, pad_dim);
		int** p_4 = p4(A_pad, B_pad, pad_dim);
		int** p_5 = p5(A_pad, B_pad, pad_dim);

		int** c_00 = c00(A_pad, B_pad, p_2, p_4, p_5, pad_dim);
		int** c_01 = c01(p_1, p_2, pad_dim);
		int** c_02 = c02(p_3, p_4, pad_dim);
		int** c_03 = c03(A_pad, B_pad, p_1, p_3, p_5, pad_dim);
		int pad_sub = pad_dim/2;
		for(int i = 0; i < pad_sub; i++)
		{
			free(p_1[i]);
			free(p_2[i]);
			free(p_3[i]);
			free(p_4[i]);
			free(p_5[i]);
		}
		free(p_1);
		free(p_2);
		free(p_3);
		free(p_4);
		free(p_5);
		
		int offset = sub_dim + 1;
		for(int i = 0; i < offset; i++)
		{
		    for(int j = 0; j < offset; j++)
		    {
		        C[i][j] = c_00[i][j];
		        if(i != sub_dim)
		        	C[i+offset][j] = c_02[i][j];
		        if(j == sub_dim){
		        	continue;
		        }
		        C[i][j+offset] = c_01[i][j];
		        if(i != sub_dim)
		        	C[i+offset][j+offset] = c_03[i][j];
		    }
		    free(c_00[i]);
		    free(c_01[i]);
		    free(c_02[i]);
		    free(c_03[i]);
		}
		free(c_00);
		free(c_01);
		free(c_02);
		free(c_03);
		for (int i = 0; i < pad_dim; i++)
	    {
	        free(A_pad[i]);
	        free(B_pad[i]);
	    }
	    free(A_pad);
	    free(B_pad);
	}
	return C;
}


int main(int argc, char *argv[])
{
    if(argc != 3){
    	printf("Run with: strassen [dimension] [matrices.txt]\n");
        return 1;
    }
    int dim = atoi(argv[1]);
    const char* inputfile = argv[2];

	int** A = make_matrix(dim);
	int** B = make_matrix(dim);
	
	// read file, store integers in A and B
	
	FILE *fp;
	fp = fopen(inputfile, "r");
	
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
    
    int **strass = multiply(A, B, dim);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("strassen: %f \n", time_spent);
	
	// prints out diagonal values in product matrix -- used for confirming correct answer, 
	// i.e. that the algorithm is working
    /* for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
        	if(i != j)
        		continue;
            printf("%i \n", strass[i][j]);
        }
    } */
	
    for (int i = 0; i < dim; i++)
    {
        free(strass[i]);
    }
    free(strass);    
}