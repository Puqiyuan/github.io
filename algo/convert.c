#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;

	fp = fopen("./T.txt", "r");

	char *s = (char*)fp;
	printf("%s\n", s);
	
	return 0;
}
