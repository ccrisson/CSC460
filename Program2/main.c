
#include "file_util.h"


char inFile[MAX_CHAR], outFile[MAX_CHAR],tmpName[MAX_CHAR],c='\0',choice='\0';

int main (int argc, char *argv[])
{
	int i=0;
         if(getInFile(argc, argv, &input));
		{
		 				
			if(getOutFile(argc, argv, &output, &listing, &tmp)) //call function for output file opening
			{
				 scanner(input,output,listing);
				 closeFiles( input,  output,  listing,  tmp); //call function to close any open files
			
			};
			
		}
	
  printf("\n\tHAVE A NICE DAY \n");
 // system ("Pause");
  return 0;
}
