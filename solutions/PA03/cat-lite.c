#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
	if(argv[1] == NULL)
	{
		char input[100];
		fgets(input,100,stdin);
		fprintf(stdout,"%s",input);
	}
	else if( strcmp(argv[1], "--help") == 0)
	{
		printf("Usage: cat-lite [--help] [FILE]...\n");
		printf("With no FILE, or when FILE is -, read standard input.\n\n");
		printf("Examples:\n");
		printf("  cat-lite README   Print the file README to standard output.\n");
		printf("  cat-lite f - g    Print f's contents, then standard input,\n");
		printf("                    then g's contents.\n");
		printf("  cat-lite          Copy standard input to standard output.\n");
		return EXIT_SUCCESS;
	}
	else
	{
		int i = 1;
		while( i < argc && argv[i] != NULL)
		{
			if( strcmp(argv[i], "-") == 0)
			{
				char string[100];
				fscanf(stdin,"%s", string);
				fprintf(stdout,"%s\n",string);
				i++;
			}
			else
			{
				FILE* fp = fopen(argv[i],"r");
				if(fp == NULL)
				{
					fprintf(stdout,"cat cannot open %s\n", argv[i]);
					return EXIT_FAILURE;
				}
				else
				{
					char buff[100];
					while( fgets(buff, 100, fp) != NULL)
					{
					fprintf(stdout,"%s", buff);				
					}
					fclose(fp);
					i++;
				}
			}
		}
	}
	return EXIT_SUCCESS;
}
