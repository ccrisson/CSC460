
#include "file_util.h"


char inFile[MAX_CHAR], outFile[MAX_CHAR],tmpName[MAX_CHAR],c='\0',choice='\0';

int main (int argc, char *argv[])
{
	int i=0;
         if(getInFile(argc, argv, &input));
		{
		 				
			if(getOutFile(argc, argv, &output, &listing, &tmp)) 	//Calls the function for opening output file 
			{
				 scanner(input,output,listing);
				 closeFiles( input,  output,  listing,  tmp); 	//Calls the function to close open files
			
			};
			
		}
	
  return 0;
}
