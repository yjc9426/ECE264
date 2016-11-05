#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMATCHING 1
#define MATCHING 0
#define ERROR 2

int matching(const char* pattern,int n,int v,int q);

int main(int argc, char* argv[])
{
	if(argc < 2){
		return ERROR;
	}
	int i = 1;
	int v = 0;
	int n = 0;
	int q = 0;
	int h = 0;
	while(i < argc-1 && argv[i] != NULL)
	{
		if( strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--invert-match")==0)
		{
			v = 1;	
		}
		else if( strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--line-number")==0)
		{
			n = 1;
		}
		else if( strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet")==0)
		{	
			q = 1;
		}
		else if( strcmp(argv[i], "--help") == 0){
			h = 1;
		}
		i++;
	}		
        // Check whether help flag is true, if so, directly print help msg and return with
        // EXIT_SUCCESS	
	if(h == 1)
	{
		printf("Usage: grep-lite [OPTION]... PATTERN\n");
		printf("Search for PATTERN in standard input. PATTERN is a \n");
		printf("string. grep-lite will search standard input line by \n");
		printf("line, and (by default) print out those lines which \n");
		printf("contain pattern as a substring.\n");
		printf("  -v, --invert-match     print non-matching lines\n");
		printf("  -n, --line-number      print line numbers with output\n");
		printf("  -q, --quiet            suppress all output\n\n");
		printf("Exit status is 0 if any line is selected, 1 otherwise;\n");
		printf("if any error occurs, then the exit status is 2.\n");
		return EXIT_SUCCESS;
	}
	// Validate pattern
	if(*(argv[argc-1])=='-'){
		fprintf(stderr, "Pattern CANNOT start with '-'!\n");
		return ERROR;
	}	

	int match;
	match = matching(argv[argc-1],n,v,q);
	if(match == 1)
		return MATCHING;
	else if(match == 0)
		return NOMATCHING;
	else
		return ERROR;	
}

int matching(const char * pattern, int n, int v, int q)
{
	int match = 0;
	int i = 1;
	char *buff = malloc (2000*sizeof(char));
	
	while(fgets(buff, 2000, stdin) != NULL){
		if(*(buff)=='\n')
			break;	
		if(strstr(buff, pattern)==NULL){
			// Not found
			if(v == 1){
				match = 1;
				if(q != 1){
					if(n == 1){
						fprintf(stdout, "%d:%s", i, buff);
					}
					else{
						fprintf(stdout, "%s", buff);
					}
				}
			}
		}
		else{
			if(v != 1){
				match = 1;
				if(q != 1){
					if(n == 1){
						fprintf(stdout, "%d:%s", i, buff);
					}
					else{
						fprintf(stdout, "%s", buff);
					}
				}
			}
		}
		i++;
	}

	free(buff);
	
	return match;
}


