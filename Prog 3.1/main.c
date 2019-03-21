/*Program 3
  CSC-460 Language Translation
  Group 9
  Chris Crisson CRI4537@calu.edu
  Matthew Bedillion BED9714@calu.edu
  Mark Blatnik BLA9072@calu.edu
  Adlene Bellaoucha BEL7984@calu.edu
*/

#include "file_util.h"


char inFile[MAX_CHAR], outFile[MAX_CHAR],tmpName[MAX_CHAR],c='\0',choice='\0';
int tokNum=0,lexErrors=0,synErrors=0,counter=0;
int main (int argc, char *argv[])
{
	int i=0;
         if(getInFile(argc, argv,&input));
		{
		 				
			if(getOutFile(argc, argv, &output, &listing, &tmp))         //Calls the function to open output file 
			{
			
				 scanner(input,output,listing);
				 closeFiles( input,  output,  listing,  tmp);       //Calls the function to close the open files
				 printf("\n There were %d tokens total",tokNum);
				 printf("\n There were %d Lexical errors\n",lexErrors);
				
			};
			
		}
	
  system ("Pause");
  return 0;
}
