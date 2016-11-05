#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	if(argc == 1)
		printf(" \n");
	int i = 1;
	while( i < argc && argv[i] != NULL)
	{
		printf("%s ", argv[i]);			
		if(argv[i+1] == NULL)	
		{
			printf("\n");
			break;
		}
		i++;
	}
	return EXIT_SUCCESS;
}
