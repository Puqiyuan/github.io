#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void computeLPSArray(char* pat, int M, int* lps); 

void KMPSearch(char* pat, char* txt) 
{ 
	int M = strlen(pat) - 1; 
	int N = strlen(txt) - 1;

	int lps[M]; 

	computeLPSArray(pat, M, lps); 

	int i = 0;
	int j = 0;
	while (i < N)
		{ 
		if (pat[j] == txt[i])
			{ 
				j++; 
				i++; 
			} 

		if (j == M)
			{ 
				printf("%d \n", i - j); 
				j = lps[j - 1]; 
			} 

		else if (i < N && pat[j] != txt[i])
			{ 
				if (j != 0) 
					j = lps[j - 1]; 
				else
					i = i + 1; 
			} 
		}
} 


void computeLPSArray(char* pat, int M, int* lps) 
{ 
	int len = 0; 

	lps[0] = 0; 


	int i = 1; 
	while (i < M)
		{ 
			if (pat[i] == pat[len])
				{ 
					len++; 
					lps[i] = len; 
					i++; 
				} 
		else
			{ 
				if (len != 0)
					{ 
						len = lps[len - 1]; 
					} 
				else
					{ 
						lps[i] = 0; 
						i++; 
					} 
			} 
		} 
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

	KMPSearch(pat, txt); 
	return 0; 
} 
