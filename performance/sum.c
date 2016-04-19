#include <stdio.h>
#include <stdlib.h>
#include "perfstats.h"

int sum(int *a, int *b, int count, int *r_a, int *r_b)
{
    int s = 0;
    int i;
    for(i = 0; i < count; i++) {
        a[i] = rand() %256;
        b[i] = rand() %256;
    }
    for(i = 0; i < count; i++) {
        *r_a += a[i];
        *r_b += b[i];
    }
    return s;
}

int main()
{
    int *a = malloc(sizeof(int)*100000000);
    int *b = malloc(sizeof(int)*100000000);
    int ra = 0;
    int rb = 0;
      perfstats_init();
      perfstats_enable();
    sum(a, b, 100000000, &ra, &rb);
    perfstats_print();
    perfstats_deinit();
    return 0;
}
