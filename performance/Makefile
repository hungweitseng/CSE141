all: perfstats.o sum sum_O3 madd hotspot hotspot_omp

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H

sum: perfstats.o sum.c 
	$(CC) $(EXTRA_CFLAGS) -O0 sum.c perfstats.o -o sum


sum_O3: perfstats.o sum.c
	$(CC) $(EXTRA_CFLAGS) -O3 sum.c perfstats.o -o sum_O3

madd: perfstats.o madd.c 
	$(CC) $(EXTRA_CFLAGS) madd.c perfstats.o -o madd

perfstats.o: perfstats.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) perfstats.c -c 

hotspot: hotspot.cu
	nvcc hotspot.cu -D_GNU_SOURCE -DREADING_FROM_BINARY perfstats.o -o hotspot -I$(INCLUDE) -L$(CUDA_LIB_DIR)  

hotspot_omp: 
	$(CC) $(CC_FLAGS) -DREADING_FROM_BINARY -fopenmp -O3 hotspot_openmp.cpp perfstats.o -o hotspot_omp

clean:
		rm -f sum sum_O3 madd hotspot hotspot_omp
		