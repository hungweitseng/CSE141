all: arraySort

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H

arraySort: arraySort.cpp perfstats.o 
	g++ $(EXTRA_CFLAGS) arraySort.cpp perfstats.o -o arraySort

perfstats.o: perfstats.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) perfstats.c -c 

clean:
		rm -f arraySort 
