#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        return 1;
    } 
    int dim = atoi(argv[1]);
    
    FILE *fp_w;
	
	fp_w = fopen("test.txt", "w");
	srand(time(NULL));
	int* buff = malloc(((2*(dim*dim))*sizeof(int)));
	for(int i = 0; i < 2*(dim*dim); i++)
	{
	    int randomBit = rand() % 2;
	    buff[i] = randomBit;
	}
	for(int i = 0; i < 2*(dim*dim); i++)
	{
	    fprintf(fp_w, "%d \n", buff[i]);
	}
	int fclose(FILE *fp_w);
	free(buff);
}