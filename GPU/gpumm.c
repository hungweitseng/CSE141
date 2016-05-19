#include <stdio.h>
#include <stdlib.h>

#include <OpenCL/opencl.h>

#include "gpumm_kernel.cl.h"

#define NUM_VALUES 1024

int main (int argc, const char * argv[]) {
  int i, j;
  char name[128];
  float *a, *b, *c;
  void *gpu_a, *gpu_b, *gpu_c;
  int ARRAY_SIZE = 128;
  dispatch_queue_t queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, NULL);
  if (queue == NULL) {
      queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_CPU, NULL);
   fprintf(stdout, "Created a dispatch queue failed\n", name);
  }
  
  cl_device_id gpu = gcl_get_device_id_with_dispatch_queue(queue);
  clGetDeviceInfo(gpu, CL_DEVICE_NAME, 128, name, NULL);
  fprintf(stdout, "Created a dispatch queue using the %s\n", name);
  
  if(argc >= 2)
    ARRAY_SIZE = atoi(argv[1]);
  a = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(cl_float));
  if(a == NULL)
   fprintf(stderr,"allocating array a failed\n");
  for(i = 0; i < ARRAY_SIZE*ARRAY_SIZE; i++)
      a[i] = (cl_float)rand();
  b = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(cl_float));
  if(b == NULL)
   fprintf(stderr,"allocating array b failed\n");
  for(i = 0; i < ARRAY_SIZE*ARRAY_SIZE; i++)
      b[i] = (cl_float)rand();
  c = (float *)malloc(ARRAY_SIZE*ARRAY_SIZE*sizeof(cl_float));
  if(c == NULL)
   fprintf(stderr,"allocating array c failed\n");

  gpu_a  = gcl_malloc(sizeof(cl_float) * ARRAY_SIZE*ARRAY_SIZE, a,
                                 CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
  gpu_b  = gcl_malloc(sizeof(cl_float) * ARRAY_SIZE*ARRAY_SIZE, b,
                                 CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
  gpu_c  = gcl_malloc(sizeof(cl_float) * ARRAY_SIZE*ARRAY_SIZE, NULL,
                                 CL_MEM_WRITE_ONLY);
  dispatch_sync(queue, ^{
   cl_ndrange range = { 2, {0, 0, 0},{ARRAY_SIZE, ARRAY_SIZE, 0},{16, 16, 0}};
   matrix_mul_kernel(&range,(cl_float*)gpu_a,(cl_float*)gpu_b,(cl_float*)gpu_c,(cl_int)ARRAY_SIZE);
   gcl_memcpy(c, gpu_c, sizeof(cl_float) * ARRAY_SIZE*ARRAY_SIZE);
  });
//   size_t wgs;
//   gcl_get_kernel_block_workgroup_info(matrix_mul_kernel,CL_KERNEL_WORK_GROUP_SIZE,sizeof(wgs), &wgs, NULL);
//        const size_t tLocal[2] = { 16, 16};
//        const size_t tGlobal[2] = { (size_t)ARRAY_SIZE, (size_t)ARRAY_SIZE };
//        cl_event event = NULL;
//  clEnqueueNDRangeKernel(queue, matrix_mul_kernel, 2, NULL, tGlobal, tLocal, 0, NULL, &event);
  gcl_free(gpu_a);
  gcl_free(gpu_b);
  gcl_free(gpu_c);
  /*
  for(i = 0; i < ARRAY_SIZE; i++)
  {
    for(j = 0; j < ARRAY_SIZE; j++)
      fprintf(stderr, "%lf ",c[i*ARRAY_SIZE+j]);
    fprintf(stderr, "\n");
  }*/
  free(a);
  free(b);
  free(c);
  dispatch_release(queue);
  return 0;
}