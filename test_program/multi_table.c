#include <stdio.h>

int main ( int argc, char *argv[] )
{
	int num=10;
	int i=0, res = 0;

	for ( i = 1 ; i <= 10 ; i++ ) {
		res = num * i;
		printf(" %d x %d = %d\n", num, i, res);
	}

	return 0;
}
