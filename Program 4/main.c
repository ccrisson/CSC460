/*Program 4
  CSC-460 Language Translation
  Group 9
  Chris Crisson CRI4537@calu.edu
  Matthew Bedillion BED9714@calu.edu
  Mark Blatnik BLA9072@calu.edu
  Adlene Bellaoucha BEL7984@calu.edu
*/

#include "file_util.h"

// global variables
char inFile[MAX_CHAR], outFile[MAX_CHAR],tmpName[MAX_CHAR],c='\0',choice='\0';
int tokNum=0,lexErrors=0,synErrors=0,counter=0;


int main (int argc, char *argv[])
{
	int flag =0;

				flag= start(&input, &output, &listing, &tmp);  //start function calls getInFile and getOutFile functions as well as returna a flag if the user wants to terminate early
				while(flag==1)
				{ 
				 scanner(input,output,listing);
				 closeFiles( input,  output,  listing,  tmp); //call function to close any open files
				 printf("\n There were %d tokens total",tokNum);
				 printf("\n There were %d Lexical errors\n",lexErrors);
					
;				 flag=0;
				 }
	
  printf("\n\tSee you soon!! \n");
  system ("Pause");
  return 0;
}





































	
	
