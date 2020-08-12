all: arithmetics arithmetics_2 

#arraySort

EXTRA_CFLAGS = -DHAVE_LINUX_PERF_EVENT_H

arithmetics: arithmetics.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) arithmetics.c -o arithmetics

arithmetics_2: arithmetics_2.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) arithmetics_2.c -o arithmetics_2

clean:
		rm -f arithmetics arithmetics_2
