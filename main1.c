#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"

int main (void)
{ 

  while(cont==0)     		 //loops until user quits the program 
  {
  	 inExist = 0; 			//reset or set flag loop to zero
  	 getInFile(inExist,cont,ext); 
  	 getOutFile(outExist,cont,ext,choice,c,inFile,outFile); 
  	 closeFiles(); 
  }
  
  printf("Input file: %s OutputFile %s", inFile, outFile);
  system ("Pause");
  return 0;
}
