#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_THREADS 4
void blockmm(double **a, double **b, double **c);
void *threaded_blockmm(void *thread_id);
double **a, **b, **c;
int n=1;
  int ARRAY_SIZE=500;

int main(int argc, char **argv)
{
  int i, j, k;
  pthread_t thread[NUM_OF_THREADS];
  int tids[NUM_OF_THREADS];
  /* initialize a, b */
  if(argc == 2)
    n = atoi(argv[1]);
  if(argc >= 3)
  {
    ARRAY_SIZE = atoi(argv[1]);
    n = atoi(argv[2]);
  }
  a = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    a[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      a[i][j] = i+j;
  }
  b = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    b[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      b[i][j] = i+j;
  }
  c = (double **)malloc(ARRAY_SIZE*sizeof(double *));
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    c[i] = (double *)malloc(ARRAY_SIZE*sizeof(double));
    for(j = 0; j < ARRAY_SIZE; j++)
      c[i][j] = 0;
  }
  /* Do matrix multiplication */
  for(i = 0 ; i < NUM_OF_THREADS ; i++)
  {
    tids[i] = i;
    pthread_create(&thread[i], NULL, threaded_blockmm, &tids[i]);
  }
  for(i = 0 ; i < NUM_OF_THREADS ; i++)
    pthread_join(thread[i], NULL);

//  blockmm(a, b, c);
  
#ifdef OUTPUT
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
    {
      printf("%lf ",c[i][j]);
    }
    printf("\n");
  }
#endif
  return 0;
}
void blockmm(double **a, double **b, double **c)
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
                c[ii][jj] += a[ii][kk]*b[kk][jj];
      }
    }
  }  
}
void *threaded_blockmm(void *thread_id)
{
  int i,j,k, ii, jj, kk;
  int chunk_size = ARRAY_SIZE/n;
  int tid = *(int *)thread_id;
//  fprintf(stderr,"TID: %d\n",tid);
  for(i = tid*chunk_size; i < ARRAY_SIZE; i+=chunk_size*NUM_OF_THREADS)
  {
    for(j = 0; j < ARRAY_SIZE; j+=chunk_size)
    {
      for(k = 0; k < ARRAY_SIZE; k+=chunk_size)
      {        
          for(ii = i; ii < i+chunk_size; ii++)
            for(jj = j; jj < j+chunk_size; jj++)
              for(kk = k; kk < k+chunk_size; kk++)
                c[ii][jj] += a[ii][kk]*b[kk][jj];
      }
    }
  }  
//  fprintf(stderr,"TID: %d finished\n",tid);
  return NULL;
}
