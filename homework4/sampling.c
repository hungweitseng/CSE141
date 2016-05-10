#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
  int i,j,k,stride,samples=1024;
  double *data, average, execution_time;
  struct timeval time_start, time_end;
  data = (double *)malloc(sizeof(double)*32768*1024);
  for(i = 0 ; i < 32768*1024; i++)
    data[i] = rand();
  for(stride = 8; stride < 65536; stride*=2)
  {
    gettimeofday(&time_start, NULL);
    for(i = 0; i < 10000; i++)
    {
      for(j=0;j<samples;j++)
        average+=data[(j*stride)%(32768*1024)];
    }
    gettimeofday(&time_end, NULL);
    execution_time = ((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0;
    fprintf(stderr, "Distance between samples: %d items, throughput: %lf MB/seconds, average = %lf\n",stride, (double)(10000*samples)/(execution_time*1024*1024), average/samples);
  }
  return 0;
}