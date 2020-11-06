#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int upper = 0, lower = 0;

void fcase(char* string, char* out)
{
	int i=0;
	//Clear out
	memset(out, 0, 255);

	if(strlen(string) != 0)
	{
		if (upper == 1)
		{
			for (i = 0; i < strlen(string); i++)
			{
				out[i] = toupper(string[i]);
			}
		}
		else if (lower == 1)
		{
			for (i = 0; i < strlen(string); i++)
			{
				out[i] = tolower(string[i]);
			}
		}
		else
		{
			strcpy(out, string);
		}
		
	}
}

int main(int argc, char **argv)
{
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	char* string = (char*)malloc(sizeof(char) * 256);
	char* out = (char*)malloc(sizeof(char) * 256);
	int index;
	int c;
	
	opterr = 0;

	if((string == NULL) || (out == NULL))
	{
		fprintf(stderr, "Erreur d'allocation mémoire");
		exit(0);
	}

	while ((c = getopt(argc, argv, "abc:")) != -1)
		switch (c)
   		{
    	case 'a':
      		aflag = 1;
      		break;
    	case 'b':
      		bflag = 1;
      		break;
    	case 'c':
      		if (strcmp(optarg, "upper") == 0)
			{
				upper = 1;
			}
			else if(strcmp(optarg, "lower") == 0)
			{
				lower = 1;
			}
			else
			{
				break;
			} 
      		break;
    	case '?':
      		if (optopt == 'c')
        		fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      		else if (isprint(optopt))
        		fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      		else
        		fprintf(stderr,"Unknown option character `\\x%x'.\n", optopt);
      		return 1;
    	default:
      		abort();
    	}

	if(bflag == 1)
		printf("\033[1;31m"); //Set text color to red
	
	sprintf(string, "aflag = %d, bflag = %d, cvalue = %s\n",
    	aflag, bflag, cvalue);
	fcase(string, out);

	printf("%s\n", out);

	for (index = optind; index < argc; index++)
	{
		sprintf(string, "Non-option argument %s\n", argv[index]);
		fcase(string, out);
		printf("%s", out);
	}
	printf("\033[0m"); //Set text color to default

	free(string);
	free(out);
	return 0;
}
