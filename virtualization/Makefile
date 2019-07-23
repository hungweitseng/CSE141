all: virtualization

virtualization: virtualization.c
	$(CC) -g -O3 virtualization.c -o virtualization
	objdump -D virtualization > virtualization.dump
clean:
	rm -f virtualization
