all: popcount popcount_inline sum sum_O3

popcount: 
	g++ -O2 popcount.cpp -o popcount

popcount_inline: 
	g++ -O2 popcount_inline.cpp -o popcount_inline 
	
sum:
	gcc -O0 sum.c -o sum

sum_O3:
	gcc -O3 sum.c -o sum_O3

dump:
	otool -tV popcount
	otool -tV popcount_inline 
	otool -tV sum
	otool -tV sum_O3
	
clean:
		rm -f popcount popcount_inline sum sum_O3
		