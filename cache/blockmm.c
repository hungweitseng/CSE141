#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int **a, **b, **c, i, j, k, ii, jj, kk, n=1;
  int ARRAY_SIZE=500;
  /* initialize a, b */
  if(argc == 2)
    n = atoi(argv[1]);
  if(argc >= 3)
  {
    ARRAY_SIZE = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  a = (int **)malloc(ARRAY_SIZE*sizeof(int *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = (int *)malloc(ARRAY_SIZE*sizeof(int));
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i][j] = i+j;
  }
  b = (int **)malloc(ARRAY_SIZE*sizeof(int *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    b[i] = (int *)malloc(ARRAY_SIZE*sizeof(int));
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i][j] = i+j;
  }
  c = (int **)malloc(ARRAY_SIZE*sizeof(int *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    c[i] = (int *)malloc(ARRAY_SIZE*sizeof(int));
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i][j] = 0;
  }
  
  /* Do matrix multiplication */
  for(i = 0; i < ARRAY_SIZE; i+=(ARRAY_SIZE/n))
  {
    for(j = 0; j < ARRAY_SIZE; j+=(ARRAY_SIZE/n))
    {
      for(k = 0; k < ARRAY_SIZE; k+=(ARRAY_SIZE/n))
      {        
          for(ii = i; ii < i+(ARRAY_SIZE/n); ii++)
            for(jj = j; jj < j+(ARRAY_SIZE/n); jj++)
              for(kk = k; kk < k+(ARRAY_SIZE/n); kk++)
                c[ii][jj] += a[ii][kk]*b[kk][jj];
      }
    }
  }  
/*
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      printf("%d ",c[i][j]);
    }
    printf("\n");
  }
*/
  return 0;
}
