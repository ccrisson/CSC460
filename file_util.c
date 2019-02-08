#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 30

#include "file_util.h"


void getInFile(int inExist, int cont, int ext) {
	int i; 
    char inFile [MAX_CHAR], c; 
    FILE *input; 
/*              INPUT FILE NAME LOOP ACCEPTS AN EXISTING NAME OR LOOPS UNTIL ONE IS FOUND OR USER ENTERS NULL           */
    while(inExist==0 && cont==0)
    {
        fflush(stdin);
        ext=0;
    printf("\nEnter an Input File Name, or Press Enter to Exit: ");  					
    memset(inFile, '\0', MAX_CHAR);                 									//Sets array inFile to NULL

    for( i=0; (c=getchar()) != '\n';i++)  //reads in user provided input file name one character at a time until line feed is detected
        {
            inFile[i]=c;
                if(c=='.')               //This determines whether an extension was added
                    ext=1;
            
        };

    if(inFile[0]=='\0')                 //if user entered nothing and pressed enter terminate the program
        cont=1;

    if(ext==0 && cont==0)               //in case no extension was provided by user, " .IN " will be attached to input filename
        strcat(inFile,".IN");

        if(cont==0)  				    //in case file was successfully opened, proceed to output file
           {
               inExist=(int)((input=fopen(inFile,"r")));       		//try opening the input file, if successful inExist !=0
           }

        if (inExist!=0)
        {
            input=fopen(inFile,"r");                                        //Open existent file for reading
            printf("\n*SUCCESS* Opened Input File: [%s] \n", inFile);       
            }
        else if(cont==0)
            printf("\n*ERROR* Input File: [%s] Could Not be Located\n", inFile);    //if file doesn't exist loop again until user exits
    };
	
}

void getOutFile(int outExist, int cont, int ext,char choice,char c, char * inFile, char * outFile) {
	
	int again, i;     
	
	while(outExist==1 && cont==0)   	//output file control loop, loops until an output file is successfully opened or user terminates
        {                               
            fflush(stdin);

            outExist=1;
            ext=0;
            choice='\0';
            again=0;
            memset(outFile, '\0', MAX_CHAR);            //nullifies the array outFile
            printf("\nEnter an Output file Name: ");
                for( i=0; (c=getchar()) != '\n';i++)   //reads in output file name a character at a time
                {
                    outFile[i]=c;
                        if(c=='.')               //determines if user added an extension or not
                            ext=1;               //if they have, set extension flag to 1 to avoid concatenating
                };                               //with the default .OUT extension

				
            if(outFile[0]=='\0')                //When NULL is entered 
            {
                for(i=0;inFile[i]!='.';i++)
                {
                  outFile[i]=inFile[i];         //if no name for the output file was provided, the input file name will be concatenated with a .OUT extension for it
                };                              
                strcat(outFile, ".OUT") ;
                output=fopen(outFile,"w");
                printf("\n*SUCCESS* Opened Output File: [%s]\n", outFile);
                strcat(outFile,".LST");
                list=fopen(outFile,"w");
                printf("\n*SUCCESS* Opened Listing File: [%s]\n", outFile);
                i=1;
                fprintf(list,"%d) ",i);
                while((c=getc(input))!=EOF)      //while input is not at the end of file, copy to output
                {
                    putc(c,output);
                    if(c=='\n')
                    {
                      c='\0';
                      i++;
                      fprintf(list,"\n%d)",i);
                    };
                    putc(c,list);
                };

                outExist=0;
                again=1;
            };

            if(ext==0 && outExist==1)
                strcat(outFile,".OUT");          //if a name was provided for the file with no extension program, " .OUT " will be attached to output file name

            if((output=fopen(outFile,"r"))&& outExist==1)               //in case a file name already exists
            {
                    printf("\n *File* [%s] already exists, Do you wish to Overwrite the file?",outFile);
                    choice=getchar();
                        if(choice == 'y'||choice=='Y')      		//inform user file about existence of the file and prompt for whether to overwrite it 
                           {
                            memset(outBak, '\0', MAX_CHAR);    		//nullifies array outBak
                            for(i=0;outFile[i]!='.';i++)
                            {
                              outBak[i]=outFile[i];
                            };
                            strcat(outBak,".BAK");          		//concatenate array outBak with a .BAK extension
                            printf("*SUCCESS*  Created a Backup File for [%s] named [%s]",outFile,outBak);
                            outbak=fopen(outBak,"w");       		//opens outbak for writing
                                while((c=getc(output))!=EOF)
                                {
                                    putc(c,outbak);        			//copy output to the backup file outbak
                                };
                                fclose(outbak);            			//close outbak
                                output=fopen(outFile,"w");  		//open output
                                strcat(outFile, ".LST");     		//concatenate a .LST extension onto outFile name
                                list=fopen(outFile,"w");     		//open the listing file
                                printf("\n*SUCCESS* Opened Listing File: [%s]\n", outFile);
                                fprintf(list,"%d) ",i);      		//print the first line number into the listing file
                                i=1;
                                while((c=getc(input))!=EOF)
                                {
                                    putc(c,output);         //copy input to output
                                    if(c=='\n')             //if the character is a newline character
                                    {
                                        c='\0';             //set c to null to ignore the newline character
                                        i++;                
                                        fprintf(list,"\n%d)",i);    //print the next line number
                                    };
                                    putc(c,list);           // print the next char in input to the listing file after the line number
                                };
                            outExist=0;
                            again=1;                        // set again flag to signal the output process is done
                           }
                        else                                                         //In case of no overwriting
                        {
                            fflush(stdin);
                            printf("\nWould You Like To Replace the File Name?");    // prompt for an alternative name
                            choice=getchar();
                                if(choice=='n'|| choice=='N')        //if not terminate the program
                                    cont=1;
                                else
                                    again=1;                     //Flag to jump back to beginning of loop
                        };                                       
            };
            if(cont==0&& again==0)                               //In case the user wants to continue and if the "again" flag isn't set
            {
                output=fopen(outFile,"w");
                printf("\n*SUCCESS* Opened Outfile: [%s]\n", outFile);
                strcat(outFile, ".LST");            //concatenate a .LST extension onto outFile name
                list=fopen(outFile,"w");            //open listing file
                printf("\n*SUCCESS* Opened Listing File: [%s]\n", outFile);
                fprintf(list,"%d) ",i);             //prints first line number into listing file
                i=1;
                while((c=getc(input))!=EOF)         //copy input to output
                {
                    putc(c,output);
                    if(c=='\n')                     //When the character is a newline character
                    {
                      c='\0';                       //set it to NULL to consume the newline
                      i++;                          
                      fprintf(list,"\n%d)",i);      //print line number to listing file
                    };
                    putc(c,list);                   //after line number print the character from input to listing file
                };
            outExist=0;         //breaks out of output loop
            };
    };
}
