
#include "file_util.h"


int getInFile(int arg_count,  char * argv[], FILE ** input)
{
    int i=0, cont = 0, ext, inExist = 0;
    char *d;
    char inFile [MAX_CHAR];

    while(inExist==0)
    {
		cont=0;
        fflush(stdin);

        if (arg_count > 1){
        	strcpy(inFile, argv[1]);
        } else {
        	printf("\n\tEnter an Input File Name, or Press Enter to Exit: ");
        	gets(inFile);
        }

//READ AND PARSE THE STRING

		if (inFile[0] != '\0')
		{
			d = strchr(inFile, '.');

				 if(d == NULL)
					strcat(inFile,".IN");


                 if(fopen(inFile,"r") != NULL)
	               inExist= 1;       //try opening the input file, if successful inExist !=0


			     if (inExist!=0)
				{
					*input=fopen(inFile,"r");                                           //Open file for reading if exists
					printf("\n\t*SUCCESS* Input File is Opened: [%s] \n", inFile);      
				}
				else
					printf("\n\t*ERROR* Input File: [%s] Could Not be Located\n", inFile);  
		}
		else
		{
			inExist=1;

		}
	}
    return inExist;

};

int getOutFile(int arg_count,  char * argv[], FILE **output, FILE **listing, FILE **tmp)
{

	int again, i, p, cont, ext, outExist;
    char c, choice;
    char outFile[MAX_CHAR],listFile[MAX_CHAR], outBak[MAX_CHAR],tmpName[MAX_CHAR];
    char *d;


	outExist = 0;
	while(outExist==0)   			//Loops until an output file is successfully opened 
    {                               		
		cont=0;
		outExist=1;
		choice='\0';

		 if (arg_count > 2){
        	strcpy(outFile, argv[2]);
        } else {
        	printf("\n\tEnter an output file name: ");
        	gets(outFile);
        }


		if (outFile != NULL)
		{
			d = strchr(outFile, '.');

				if(d == NULL)
                   strcat(outFile, ".OUT") ;

				 if((fopen(outFile,"r")))
				 {

					 printf("\tThis file name is already in use.\n");
					 printf("\tWould you like to overwrite it?");
					 choice=getchar();
						if(choice=='Y' || choice == 'y')
						{
							 copy_backup(outFile);
						};


				 };

                *output=fopen(outFile,"w");                                      //opens the output file searches for the '.' keeps only
                printf("\n\t*SUCCESS* Opened  Output  File: [%s]", outFile);	 //that which comes before the '.' and adds .lst extern
				memset(listFile, '\0', MAX_CHAR);		 //after that open listing file with .lst extension
				d = strchr(outFile, '.');
				p = (int)(d - outFile);
				strncpy(listFile, outFile, p);
                strcat(listFile,".LST");
                *listing=fopen(listFile,"w");
                printf("\n\t*SUCCESS* Opened  Listing File: [%s]\n", listFile);
                outExist=1;

		};
		return outExist;
	}

};


void copy_backup(char *outFile)   //Copies current contents of output to backup file
{
	int p;
	char *d;
	char outBak[MAX_CHAR];
	FILE *back_up, *output;


	output=fopen(outFile,"r");      					//Open local file output and set it to outFile
	memset(outBak,'\0',MAX_CHAR);  						//Clears outBak array
	d = strchr(outFile, '.');     						//Locate first instance of '.'
	p = (int)(d - outFile);							//Subtract remaining string to get integer value of letters before the .
	strncpy(outBak, outFile, p);  						//Copy to the dot
	strcat(outBak,".BAK");   						//Concatenate .BAK extension
	back_up=fopen(outBak,"w");  						//Open backup for writing
	printf("\n\t*SUCCESS* Created Backup  File: [%s]",outBak);

	char c;

    while((c=getc(output))!=EOF)        //while output is not at the end of file copy to backup
    {
        putc(c,back_up);
  	};
	fclose(output);			//Close local output
	fclose(back_up);		//Close backup
}
void printToken(FILE *input, FILE *output, FILE *listing,token tok[])
{

    static int j;
	char c;
	char begin[]="BEGIN";
	char end[]="END";
	char read[]="READ";
	char write[]="WRITE";
	char IF[]="IF";
	char ENDIF[]="ENDIF";
	char GOTO[]="GOTO";
	char integer[]="INTEGER";
	char var[]="VARIABLE";
	char err[]="ERROR";
	char lpar[]="LEFT PARANTHESIS";
	char rpar[]="RIGHT PARANTHESIS";
	char semi[]="SEMI COLON";
	char comma[]="COMMA";
	char assign[]="ASSIGNMENT OPERATOR";
	char add[]="ADDITION OPERATOR";
	char sub[]="SUBTRACTION OPERATOR";
	char less[]="LESS THAN OPERATOR";
	char great[]="GREATER THAN OPERATOR";
	char eq[]="EQUALS OPERATION";
	char scaneof[]="SCAN EOF";

		int i;
		for(i=0;i<tok[i].len;i++)        
		{

			if(*tok[i].str =='\0' ||  tok[i].num!=10)   	//If blank line or not an error, print it
			{
				j++;
				fprintf(listing,"%d) ",j);
				fprintf(listing,"%s",tok[i].str);
			}
				else 					
				{

					fprintf(listing,"ERROR Not Recognized [%.*s]\n ",tok[i].len,tok[i].str);
				}



			if(tok[i].num==1)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, begin,tok[i].len,tok[i].str );
			else if(tok[i].num== 2)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, end,tok[i].len,tok[i].str );
			else if(tok[i].num== 3)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, read,tok[i].len,tok[i].str );
			else if(tok[i].num== 4)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, write,tok[i].len,tok[i].str );
			else if(tok[i].num== 5)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, IF,tok[i].len,tok[i].str );
			else if(tok[i].num== 6)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, ENDIF,tok[i].len,tok[i].str );
			else if(tok[i].num== 7)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n",tok[i].num, GOTO,tok[i].len,tok[i].str );
			else if(tok[i].num==8)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE: %s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, var, tok[i].len,tok[i].str);
			else if(tok[i].num==9)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, integer,tok[i].len, tok[i].str);
			else if(tok[i].num==10)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, err, tok[i].len,tok[i].str);
			else if(tok[i].num==11)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, lpar,tok[i].len, tok[i].str);
			else if(tok[i].num==12)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, rpar, tok[i].len,tok[i].str);
			else if(tok[i].num==13)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, semi, tok[i].len,tok[i].str);
			else if(tok[i].num==14)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, comma, tok[i].len,tok[i].str);
			else if(tok[i].num==15)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, assign,tok[i].len, tok[i].str);
			else if(tok[i].num==16)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, add, tok[i].len,tok[i].str);
			else if(tok[i].num==17)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, sub,tok[i].len, tok[i].str);
			else if(tok[i].num==18)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, less,tok[i].len, tok[i].str);
			else if(tok[i].num==19)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, great, tok[i].len,tok[i].str);
			else if(tok[i].num==20)
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, eq,tok[i].len, tok[i].str);
			else
				fprintf(output,"TOKEN NUMBER:\t\t %dTOKEN TYPE:%s\t\t ACTUAL TOKEN:%.*s\n", tok[i].num, scaneof,tok[i].len, tok[i].str);


	};
}

void closeFiles(FILE *input, FILE *output, FILE *listing, FILE *tmp)
{
	if(input)
		fclose(input);
	if(output)
		fclose(output);
	if(listing)
		fclose(listing);
	if(tmp)
		fclose(tmp);

};

void scanner (FILE *input, FILE *output, FILE *listing)
{
	token tok[MAXBUFF];
	char c;
	char lineBuff[MAXBUFF];
	 int count=0,i=0;
	clear_lineBuff(lineBuff);					//Make sure line buff is empty
	while(fgets(lineBuff,MAXBUFF,input) !=NULL)			//Gets a line from input
	{
		i++;
		count=Tokenize(lineBuff,tok);				//Calls func tokenize and returns number of tokens on that line
		printf("\nLine %d has %d tokens:",i,count);
		ident_token(count,tok);
		clear_lineBuff(lineBuff);				//Clears the line buffer for next line

	}

}

void clear_lineBuff(char * lineBuff)
{
	memset(lineBuff,'\0',MAXBUFF);					//Sets the value of lineBuff to null
}


int Tokenizer(char *linebuffer, token tokenslots[])	//tokenizes it
{
	char *beginning_token;
	int counter =0;
	int typechecker = 0;
	int symchecker = 3;
	int alphachecker = 1;
	int numchecker = 2;
	int typecheckprev = 0;
	while(*linebuffer)
		{
			while(isspace(*linebuffer)) //skip all that nasty white space
			{
				linebuffer++;
			}
			//printf("\t %c",linebuffer); <-nothing in the line buffer
			beginning_token = linebuffer;  //find the beginning
			if(isalpha(*linebuffer))
			{
				typechecker = 1;
			}
			else if(isdigit(*linebuffer))
			{
				typechecker = 2;
			}
			else if(isspace(*linebuffer))
			{
				linebuffer++;
			}
			else
			{
				typechecker = 3;
			}
			typecheckprev = typechecker;
		//	printf("%c",beginning_token);
		//	system("PAUSE");
			while(*linebuffer && !isspace(*linebuffer) && typechecker == typecheckprev) //a space is found lets keep grabbing
			{
				linebuffer++; //next token please
				if(isalpha(*linebuffer))
				{
					typechecker = 1;
				}
				else if(isdigit(*linebuffer))
				{
					typechecker = 2;
				}
				else if(isspace(*linebuffer))
				{
					
				}
				else
				{
					typechecker = 3;
				}
			}
				typecheckprev = typechecker;
			
				if(counter < MAX_BUFFER) //checkin if we found the end
				{
				//	printf("\n \t %c \n", beginning_token);
				//	system("PAUSE");
					tokenslots[counter].str=beginning_token; //puttin it inside
					tokenslots[counter].length = linebuffer - beginning_token; //grabbing the length of the token
				//	printf(" \t  %[%.*s]", tokenslots);
				//	system("PAUSE");
				//linebuffer++; //lets continue on
				}
				counter++;
	
		}
		counter--; //ARE YOU KIDDING ME THIS WORKS OM GOODNESS GRACIOUS
		linebuffer++;
		return counter; //return the counter

}

void ident_token(int count, token tok[])
{
	int resWord=0,isInt=0,isSym=0;
	token tmp;
	int i;
	for(i=0; i<count;i++)
	{
		tmp.str=0;
		tmp.len=0;
		tok[i].num=0;
		resWord=0;
		if (isalpha(*tok[i].str))  		//In case the string begins with an alpha
		{

			tmp.str=tok[i].str;		
			tmp.len=tok[i].len;
			resWord=checkReserved(tmp);  	//Pass tmp token into function to check if reserved
			tok[i].num=resWord;
			if(tok[i].num<8)		
			{
				printf("\n\t[%.*s]IS A RESERVED WORD ENUM %d",tmp.len,tmp.str,tok[i].num);


			}
			if(tok[i].num == 8)		
			{
				printf("\n\t[%.*s] IS A VARIABLE ENUM %d",tmp.len,tmp.str,tok[i].num);

			}
			printToken(input,output,listing,tok);		//Printing the token		
		}

		else if(isdigit(*tok[i].str))		//Check if the token begins with an integer
		{
			tmp.str=tok[i].str;
			tmp.len=tok[i].len;
			printf("\n\t[ %.*s ]",tmp.len,tmp.str);
			isInt=checkInt(tmp);				//checks if all of the string is digits, returns 1 if not int
			tok[i].num=isInt;				// assigns either 1 or 0 to struct value. 1= is not an int 0= is an int
				if(tok[i].num==9)			// ints are enum 9
				{
					printf(" IS AN INT ENUM %d",tok[i].num);

				}
				else					//In case string contains any character other than int
				{
					printf(" IS A LEX ERROR %d", tok[i].num);

				}

			printToken(input,output,listing,tok);		//Printing the token
		}
		else
		{
			tmp.str=tok[i].str;
			tmp.len=tok[i].len;
			printf("\n\t[ %.*s ]",tmp.len,tmp.str);
			isSym=checkSymbol(tmp);				//Checks if token is any of the reserved characters
			tok[i].num=isSym;
				if(tok[i].num>10 && tok[i].num<21)		
				{
					printf(" IS A SYMBOL ENUM %d", tok[i].num);

				}
				else				//If not an aplha digit or a symbol, an error will occur
				{
					printf(" IS A LEX ERROR ENUM %d",tok[i].num);

				}
			printToken(input,output,listing,tok);				//Printing the token
		}



	}

}


int checkReserved(token tmp)
{

	char string[MAX_CHAR];
	int resWord=0;
	memset(string,'\0',MAX_CHAR);
	strncpy(string, tmp.str,tmp.len);

	 if(strcasecmp(string,"begin")==0)
		 resWord=1;
	 else if (strcasecmp(string,"END") ==0 )
		resWord=2;
	 else if (strcasecmp(string, "READ")==0)
		resWord=3;
	 else if (strcasecmp(string,"WRITE")==0 )
		resWord=4;
	 else if (strcasecmp(string,"IF") ==0)
		resWord=5;
	 else if (strcasecmp(string,"ENDIF")== 0)
		resWord=6;
	 else if (strcasecmp(string,"GOTO") ==0)
		resWord=7;

	else
		resWord=8;


	return resWord;


}

int checkInt(token tmp)
{

	int digit=9;
	const char *ptr;
	ptr=tmp.str;

	int i;
	for(i=0; i<tmp.len;i++)				//Size of the token
	{

		if(!isdigit(*ptr))			//Check if pointer is a digit
			digit=10;			//In case of not a digit, give it enum 10 for lexical error
		ptr++;							
	}
	return digit;

}
int checkSymbol(token tmp)
{
	char string[MAX_CHAR];
	int sym=0;
	memset(string,'\0',MAX_CHAR);
	strncpy(string, tmp.str,tmp.len);		//Check if it matches any reserved tokens

	 if(strcmp(string,"(")==0)
		 sym=11;
	 else if (strcmp(string,")") ==0 )
		sym=12;
	 else if (strcmp(string, ";")==0)
		sym=13;
	 else if (strcmp(string,",")==0 )
		sym=14;
	 else if (strcmp(string,":=") ==0)
		sym=15;
	 else if (strcmp(string,"+")== 0)
		sym=16;
	 else if (strcmp(string,"-") ==0)
		sym=17;
	 else if(strcmp(string,"<") ==0)
		 sym=18;
	 else if(strcmp(string,">")==0)
		 sym=19;
	 else if(strcmp(string,"=")==0)
		 sym=20;

	else						//In case of not, it is a lexical error enumerated 10
		sym=10;


	return sym;
}










