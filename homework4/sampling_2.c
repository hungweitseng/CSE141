#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
  int i,j,k,stride=8,samples=4194304,size=4096;
  double *data, average, execution_time;
  struct timeval time_start, time_end;
  data = (double *)malloc(sizeof(double)*32768*1024);
  for(i = 0 ; i < 32768*1024; i++)
    data[i] = rand();
  for(size = 1024; size < 32768*1024; size*=2)
  {
    gettimeofday(&time_start, NULL);
    for(i = 0; i < 8; i++)
    {
      for(j = 0; j < samples/8; j++)
        average+=data[(j*stride+i)%(size)];
    }
    gettimeofday(&time_end, NULL);
    execution_time = ((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0;
    fprintf(stderr, "Array size: %d items, throughput: %lf MB/seconds average = %lf\n",size,stride, (double)(8*samples)/(execution_time*1024*1024), average/samples);
  }
  return 0;
}