

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbolTable.h>
#include <codeGeneration.h>





void makeCodeDeclaration(char* identifier, Type type, char* value)
{
    if (type == INTEGER)
    {
        if (value == NULL)
        	fprintf(out_file, "%s: dd 0\n", identifier);

        else
        {
        	int x = atoi(value);
        	fprintf(out_file, "%s: dd %d\n", identifier, x);
        }
    }

    else if (type == REAL)
    {
    	if (value == NULL)
        	fprintf(out_file, "%s: dq 0 \n", identifier);

        else
        {
          	double x = atof(value);
        	fprintf(out_file, "%s: dq %f\n", identifier, x);
        }
    }

    else if (type == STRING)
    {
    	if (value == NULL)
        	fprintf(out_file, "%s: db 0 \n", identifier);

        else
        {
          	fprintf(out_file, "%s: db %s, 0\n", identifier, value);
        }
    }
}