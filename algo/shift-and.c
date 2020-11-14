#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int preprocess(unsigned int B[], char *pat, int n)
{
    unsigned int shift = 1;
	
    for (int i = 0; i < n; i++)
		{
			B[ (int)pat[i] ] |= shift;
			// printf("B[ %d ]: %u\n", (int)pat[i], B[ (int)pat[i] ]);
			shift <<= 1;
		}
	return 0;
}

int and_match(char *txt, char *pat)
{
    int m = strlen(txt) - 1, n = strlen(pat) - 1;
    unsigned int B[256], D = 0, mask;
	
    for (int i = 0; i < 256; i++)
        B[i] = 0;
    preprocess(B, pat, n);

    mask  = 1 << (n - 1);
    for (int i = 0; i < m; i++)
		{
			D = (D << 1 | 1) & B[(int)txt[i]];
			if (D & mask)
				printf("%d\n", i - n + 1);
		}

    return 0;
}

int convert(char *filename, char *str)
{
	long int i = 0;
	char ch;
	FILE *fp = fopen(filename, "r");

	while ((ch = fgetc(fp)) != EOF)
		{
			str[i] = ch;
			i++;
		}

	return 0;
}

int main()
{
	char *txt = (char*)malloc(3774 * sizeof(char));
	char *pat = (char*)malloc(10 * sizeof(char));

	convert("./largeEWD.txt", txt);
	convert("./pat.txt", pat);

	and_match(txt, pat);
	
    return 0;
}
