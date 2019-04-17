#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

off_t fsize(const char *filename)
{
	struct stat st;
	
	if (stat(filename, &st) == 0)
		return st.st_size;

	fprintf(stderr, "Cannot determine size of %s: %s\n",
					filename, strerror(errno));
	return -1;
}

void preprocess(unsigned int B[], char* T)
{
	unsigned int shift = 1;
	char ch;
	FILE *Tfp;
	Tfp = fopen(T, "r");
	
	while ((ch = fgetc(Tfp)) != EOF)
		{
			B[(int)ch] |= shift;
			shift <<= 1;
		}
}

int shift_and(char *S, char *T)
{
	FILE *Sfp;
	unsigned int B[256], D = 0, mask;
	char ch;
	int i;

	Sfp = fopen(S, "r");
	
	for (i = 0; i < 256; i++)
		B[i] = 0;
	preprocess(B, T);

	long int n = fsize(T);
	mask  = 1 << (n - 2);

	while ((ch = fgetc(Sfp)) != EOF)
		{
			D = (D << 1 | 1) & B[(int)ch];
			if (D & mask)
				{
					printf("%ld\n", ftell(Sfp) - n + 2);
				}
		}

	return 0;
}

int main()
{
	char S[] = "./S.txt";
	char T[] = "./T.txt";
	
	shift_and(S, T);
	
	return 0;
}
