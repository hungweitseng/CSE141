#include <stdio.h>
#include <stdlib.h>

void blockmm(float *a, float *b, float *c);
int n=1;
int ARRAY_SIZE=128;
int main(int argc, char **argv)
{
  float *a, *b, *c;
  int i, j, k;
  /* initialize a, b */
  if(argc == 2)
    n = atoi(argv[1]);
  if(argc >= 3)
  {
    ARRAY_SIZE = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  a = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(float));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i*ARRAY_SIZE+j] = rand();
  }
  b = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(float));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i*ARRAY_SIZE+j] = rand();
  }
  c = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(float));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i*ARRAY_SIZE+j] = 0;
  }
  blockmm(a, b, c);
  
  /* Do matrix multiplication */
/*
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      fprintf(stderr,"%lf ",c[i*ARRAY_SIZE+j]);

    }
    fprintf(stderr,"\n");
  }
*/
  return 0;
}
void blockmm(float *a, float *b, float *c)
{
  int i,j,k, ii, jj, kk;
  for(i = 0; i < ARRAY_SIZE; i+=(ARRAY_SIZE/n))
  {
    for(j = 0; j < ARRAY_SIZE; j+=(ARRAY_SIZE/n))
    {
      for(k = 0; k < ARRAY_SIZE; k+=(ARRAY_SIZE/n))
      {        
          for(ii = i; ii < i+(ARRAY_SIZE/n); ii++)
            for(jj = j; jj < j+(ARRAY_SIZE/n); jj++)
              for(kk = k; kk < k+(ARRAY_SIZE/n); kk++)
                c[ii*ARRAY_SIZE+jj] += a[ii*ARRAY_SIZE+kk]*b[kk*ARRAY_SIZE+jj];
      }
    }
  }  
}
