#include <stdio.h>
#include <stdint.h>

int r[2800 + 1];
uint64_t i, k;
int b, d;
int c = 0;

uint64_t tot;

int main() {
    

    for (i = 0; i < 2800; i++) {
	r[i] = 2000;
    }
    r[i] = 0;

    tot = i;

    for (k = 2800; k > 0; k -= 14) {
	d = 0;

	i = k;
	for (;;) {
	    d += r[i] * 10000;
	    b = 2 * i - 1;

	    r[i] = d % b;
	    d /= b;
	    i--;
	    if (i == 0) break;
	    d *= i;
	}
	printf("%.4d", c + d / 10000);
	c = d % 10000;
    }

    printf("Computed %llu digits of pi \n", tot / 4 );

    return 0;
}