#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
  int i,j,k,stride,samples=1024;
  double *data, average;
  struct timeval time_start, time_end;
  data = (double *)malloc(sizeof(double)*32768*1024);
  for(i = 0 ; i < 32768*1024; i++)
    data[i] = rand();
  for(stride = 8; stride < 65536; stride*=2)
  {
    gettimeofday(&time_start, NULL);
    for(i = 0; i < 100000; i++)
    {
      for(j=0;j<samples;j++)
        average+=data[(j*stride)%(32768*1024)];
    }
    gettimeofday(&time_end, NULL);
    fprintf(stderr, "Sampled %d numbers from every %d numbers: %lf seconds,  average = %lf\n",samples,stride,((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0, average);
  }
  return 0;
}