all: testloop testloop_O3 coherence blockmm blockmm_pthread

testloop_O3: testloop.c
	gcc -O3 -g testloop.c -lpthread -o testloop_O3
	otool -tV testloop_O3 > testloop_O3.dump 


testloop: testloop.c
	gcc -O0 -g testloop.c -lpthread -o testloop 
	otool -tV testloop > testloop.dump 

coherence: coherence.c
	gcc -O0 coherence.c -lpthread -o coherence 

blockmm_pthread: blockmm_pthread.c
	gcc -O3 blockmm_pthread.c -lpthread -o blockmm_pthread

blockmm: blockmm.c
	gcc -O3 blockmm.c -lpthread -o blockmm 


clean:
		rm -f testloop testloop_O3 coherence blockmm blockmm_pthread *.dump *~
		rm -rf *.dSYM
