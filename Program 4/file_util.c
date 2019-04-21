
#include "file_util.h"

int start(FILE **input, FILE **output, FILE **listing, FILE **tmp)
{
	int var=0;
	var=getInFile(input);
	if(var==1)
		getOutFile( output, listing, tmp);

		return var;
}

int getInFile(FILE **input) 
{
/* INPUT FILE NAME LOOP ACCEPTS AN EXISTING NAME OR LOOPS UNTIL ONE IS FOUND OR USER ENTERS NULL  */
    int i=0, cont = 0, inExist = 0;
    char *d;
    extern char inFile [MAX_CHAR];
	
	memset(inFile, '\0',MAX_CHAR);
    while(inExist==0)
    {
		cont=0;
        fflush(stdin);
		printf("\n\tEnter an Input File Name, or Press Enter to Exit: ");  
    }

//READ AND PARSE THE STRING
	
	gets(inFile);
		if (inFile[0] != '\0' || inFile[0]!= NULL)
		{
			d = strchr(inFile, '.');

				 if(d == NULL)
					strcat(inFile,".IN");


                 if(fopen(inFile,"r") != NULL)
	               inExist= 1;       //try opening the input file, if successful inExist !=0


			     if (inExist!=0)
				{
					*input=fopen(inFile,"r");                                        //if file exists open it for reading
					printf("\n\t*SUCCESS* Opened Input File: [%s] \n", inFile);       //inform user input file successfully opened
				}
				else 
					printf("\n\t*ERROR* Input File: [%s] Could Not be Located\n", inFile);    //if file doesn't exist loop again until user exits
		}
		else
		{
			inExist=2;
		}
	}
    return inExist;	
};

int getOutFile(FILE **output, FILE **listing, FILE **tmp)
{

	int i, p, cont, outExist;
    char choice;
    char outFile[MAX_CHAR],listFile[MAX_CHAR];
    char *d;
	extern char inFile[MAX_CHAR];
	extern char tmpName[MAX_CHAR];
	

	outExist = 0;
	while(outExist==0)   //output file control loop, loops until an output file is
    {                               //successfully opened or user terminates
		cont=0;
		outExist=0;
		choice='\0';
		memset (tmp, '\0',MAX_CHAR );
		memset(outFile,'\0',MAX_CHAR);
		
        printf("\n\tEnter an Output file Name: ");
		gets(outFile);
		
		
		if (outFile != NULL )
		{
			d = strchr(outFile, '.');

			if(d == NULL)
               strcat(outFile, ".OUT") ;

				if((fopen(outFile,"r")))
				{
					
					 printf("\tThis File Name is Already in Use.\n");
					 printf("\tWould You Like To OverWrite It?");
					 choice=getchar();
						if(choice=='Y' || choice == 'y')
						{
							 copy_backup(outFile);
							 cont=1;
						}
						
				}
				 else(cont=1);
				 
				if(cont==1)
				{
					*output=fopen(outFile,"w"); 

					strcpy(tmpName,outFile);
					strcat(tmpName, ".TMP");
					*tmp=fopen(tmpName, "w");								            //opens output file searches for the '.' keeps only 
					printf("\n\t*SUCCESS* Opened  Output  File: [%s]", outFile);		// that which comes before the '.' and adds .lst extern		
					memset(listFile, '\0', MAX_CHAR);								    //after that open listing file with .lst extension
					d = strchr(outFile, '.');
					p = (int)(d - outFile);
					strncpy(listFile, outFile, p);
					strcat(listFile,".LST");
					*listing=fopen(listFile,"w");
					printf("\n\t*SUCCESS* Opened  Listing File: [%s]\n", listFile);
					outExist=1;
				}
			
		}
	
		else
		{
			for(i=0;inFile[i]!='\0';i++)
			{
				outFile[i]=inFile[i];
			}
			
			
		}
	}
          return outExist;              
};


void copy_backup(char *outFile)   // copies current contents of output to backup file
{
	int p;
	char *d;
	char outBak[MAX_CHAR];
	FILE *back_up, *output;
	
	output=fopen(outFile,"r");      						// open local file output and set it to outFile
	memset(outBak,'\0',MAX_CHAR);  							// clears outBak array
	d = strchr(outFile, '.');     							// locate first instance of '.'
	p = (int)(d - outFile);									// subtract remaining string from outFile to get integer value of lettters before the .
	strncpy(outBak, outFile, p);  							// copy to the dot
	strcat(outBak,".BAK");   							    //concatenate .BAK extension
	back_up=fopen(outBak,"w");  							//open backup for writing
	printf("\n\t*SUCCESS* Created Backup  File: [%s]",outBak);
	
	char c;
   
    while((c=getc(output))!=EOF)      //while output is not at the end of file copy to backup
    {
        putc(c,back_up);
  	};
									  //since backup file will be used outside this function close both local output and backup
		fclose(back_up);
}
void printToken(FILE *input, FILE *output, token tok [],int count,char *lineBuff)
{
	
    int j=0;
	char BEGIN[]="BEGIN";
	char END[]="END";
	char READ[]="READ";
	char WRITE[]="WRITE";
	char IF[]="IF";
	char THEN[]="THEN";
	char ELSE[]="ELSE";
	char ENDIF[]="ENDIF";
	char WHILE[]="WHILE";
	char ENDWHILE[]="ENDWHILE";
	char GOTO[]="GOTO";
	char AND[]="AND";
	char OR[]="OR";
	char integer[]="INTEGER";
	char var[]="VARIABLE";
	char err[]="LEXICAL ERROR";
	char lpar[]="LEFT PARANTHESIS";
	char rpar[]="RIGHT PARANTHESIS";
	char semi[]="SEMI COLON";
	char comma[]="COMMA";
	char assign[]="ASSIGNMENT OPERATOR";
	char add[]="ADDITION OPERATOR";
	char sub[]="SUBTRACTION OPERATOR";
	char mult[]="MULTIPLICATION OPERATOR";
	char div[]="DIVISION OPERATOR";
	char less[]="LESS THAN OPERATOR";
	char lesseq[]="LESS OR EQUAL TO";
	char great[]="GREATER THAN OPERATOR";
	char greateq[]="GREATER OR EQUAL TO";
	char eq[]="EQUALS OPERATION";
	char noteq[]="NOT EQUAL TO";
	char scaneof[]="SCAN EOF";
	char NOT[]="NOT";
	
    
	extern int tokNum;	
	int i=0;
		

			for( i=tokNum-count; i<tokNum;i++)
			{

			
			 if(tok[i].num==1)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, BEGIN,tok[i].str );
			 else if(tok[i].num== 2)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, END,tok[i].str );
			 
			 else if(tok[i].num== 3)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, READ,tok[i].str );
			 
			  else if(tok[i].num== 4)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, WRITE,tok[i].str );
			
			  else if(tok[i].num== 5)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, IF,tok[i].str );
			 
			  else if(tok[i].num== 6)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, THEN,tok[i].str );
			 
			 else  if(tok[i].num== 7)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, ELSE,tok[i].str );
			 
			 else  if(tok[i].num==8)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, ENDIF, tok[i].str);
			 
			 else  if(tok[i].num==9)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, WHILE, tok[i].str);
			 
			 else  if(tok[i].num==10)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, ENDWHILE ,tok[i].str);
			 
			 else  if(tok[i].num==11)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, GOTO, tok[i].str);
			 
			 else  if(tok[i].num==12)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, AND, tok[i].str);
			 
			 else  if(tok[i].num==13)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, OR, tok[i].str);
			 
			 else  if(tok[i].num==14)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, var, tok[i].str);
			 
			 else  if(tok[i].num==15)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, integer,tok[i].str);
			 
			 else  if(tok[i].num==16)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, err, tok[i].str);
				
			 
			 else  if(tok[i].num==17)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n",   tok[i].num, lpar, tok[i].str);
			 
			 else  if(tok[i].num==18)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, rpar, tok[i].str);
			 
			  else if(tok[i].num==19){
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n",tok[i].num, semi, tok[i].str);
				fprintf(output,"\n%s\n",lineBuff);
			  }
			 
			  else if(tok[i].num==20)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t\t ACTUAL TOKEN: %s\n", tok[i].num, comma,tok[i].str);
			 
			  else if(tok[i].num==21)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %s\n",   tok[i].num, assign, tok[i].str);
			 
			  else if(tok[i].num==22)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, add, tok[i].str);
			 
			  else if(tok[i].num==23)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %s\n", tok[i].num, sub, tok[i].str);
			 
			  else if(tok[i].num==24)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %s\n", tok[i].num, mult, tok[i].str);
	
			  else if(tok[i].num==25)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, div, tok[i].str);
			 
			  else if(tok[i].num==26)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, less, tok[i].str);
			 
			  else if(tok[i].num==27)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, lesseq, tok[i].str);
			 
			 else  if(tok[i].num==28)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %s\n", tok[i].num, great, tok[i].str);
			 
			  else if(tok[i].num==29)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t ACTUAL TOKEN: %s\n", tok[i].num, greateq, tok[i].str);
			 
			  else if(tok[i].num==30)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, eq, tok[i].str);
			 
			  else if(tok[i].num==31)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, noteq, tok[i].str);
			  else if(tok[i].num==32)
				fprintf(output,"TOKEN NUMBER: %d \t\t TOKEN TYPE: %s\t\t ACTUAL TOKEN: %s\n", tok[i].num, NOT, tok[i].str);
			 
	
			
			}
	
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
	if(back_up)
		fclose(back_up);
};

void scanner (FILE *input, FILE *output, FILE *listing)
{
	extern FILE *tmp;
	extern char outFile[MAX_CHAR];
	token tok[MAXBUFF];
	char c;
	char lineBuff[MAXBUFF];
	int tokperline[MAXBUFF];
	 int count=0,i=0,j=0,k=0;
	clear_lineBuff(lineBuff);	
	for(i=0;i<MAXBUFF;i++)
		for(j=0;j<MAX_CHAR;j++)
		{
			tok[i].str[j]=0;
		}
		i=0;
		j=0;
		k=0;
	for( k=0;k<MAXBUFF;k++)
		tokperline[k]=0;
	
	while(fgets(lineBuff,MAXBUFF,input) !=NULL)				//gets a line from input
	{
		i++;
		
		count=Tokenize(lineBuff,tok);					//calls func tokenize and returns number of tokens on that line
		tokperline[i-1]=count;
		printf("\nLine %d has %d tokens:",i,count);
		ident_token(count,tok);
		//printToken(input,output,tok,count,lineBuff);
		clear_lineBuff(lineBuff);						//clears the line buffer for next line
	}
	
	if(input)
	fclose(input);
	ParseTokens(tok,tokperline);
	 appendFiles();

		
}
int delim(char lineBuff)
{
	int isDelim =0;
	if (lineBuff == '(' || lineBuff == ')' || lineBuff == 'AND' || lineBuff == 'OR' || lineBuff == 'NOT' ||
		lineBuff == '=' || lineBuff == ':=' || lineBuff == '-' || lineBuff == '+' || lineBuff == '*' ||
		lineBuff == '/' || lineBuff == '>' || lineBuff == '<' || lineBuff == '>=' || lineBuff == '<=' ||
		lineBuff == '<>' || lineBuff == ';' || lineBuff == ','|| lineBuff==':')
	{
		isDelim=1;					//checks to see if the character is a known delimter
	}
	else
		isDelim=0;

	return isDelim;
}
void clear_lineBuff(char * lineBuff)				
{
	memset(lineBuff,'\0',MAXBUFF);				//sets value of line buff to null
}

int Tokenize( char *lineBuff,  token tok[])
{
	
	int count=0,i=0,j=0;
	extern int tokNum;
	
 	while(*lineBuff && *lineBuff!= 13 && *lineBuff!=10)       //dereference linebuff and loop while not null, or linefeed or blank
	{	
		
		while(isspace(*lineBuff))		//consume leading whitespace
			{			
				lineBuff++;			
			}
	
		while (delim(*lineBuff) == 0 && *lineBuff && *lineBuff != 13 && *lineBuff != 10)  //if not null or delimiter or carriage return or linefeed
			{
				tok[tokNum].str[j] = *lineBuff;				//store it 
				lineBuff++;									// go to next character
				j++;										//inc j to advance the tokens string array
			}
				count++;					//inc token count
				tokNum++;					// inc total num of tokens
				j = 0;						//reset string array index back to 0
		 while (delim(*lineBuff)!=0 && *lineBuff && *lineBuff != 13 && *lineBuff != 10)				//is it is a delimiter
			{
				if(*lineBuff=='<' || *lineBuff =='>' || *lineBuff == ':')						//check to see if it is a possible 2 character delimiter
				{ 
					tok[tokNum].str[j] = *lineBuff;									//if it is store it and advance to the next character
					lineBuff++;
					if (*lineBuff == '>' || *lineBuff == '=')				//if it matches a known two charcter delimiter inc the string index and store it as one token
						{
							j++;
							tok[tokNum].str[j]=*lineBuff;
							lineBuff++;
						}
					count++;					//inc token count
					tokNum++;
					j=0;
				}
				else                                           // else it isnt a possible two character selimiter so store it 
				{
					tok[tokNum].str[j] = *lineBuff;
					lineBuff++;
					count++;					//inc token count
					tokNum++;
					j = 0;
				}
			}
		

	}
	
	return count;
}	

void ident_token(int count, token tok[])
{
	int resWord=0,isInt=0,isSym=0,j=0;
	extern int tokNum;
	int i=0;
	for( i=tokNum-count; i<tokNum;i++)   //i is equal to the total number of tokens minus the number of tokens in the lineBuff
	{
	
		tok[i].num=0;
		resWord=0;
		j=0;
		
		if (isalpha(tok[i].str[j]))  //if the string begins with an alpha
		{
			resWord=checkReserved(tok[i]);  //pass tmp token into function to check if it is reserved
			tok[i].num=resWord;
			if(tok[i].num<14 || tok[i].num == 32)			// reserved words are enum status 1-7
				printf("\n\t[%s]IS A RESERVED WORD ENUM %d", tok[i].str,tok[i].num);
				
			else                  		//variable are enum 8
				printf("\n\t[%s] IS A VARIABLE ENUM %d",tok[i].str,tok[i].num);
		}
		
		else if(isdigit(tok[i].str[j]))		//see if token begins with int
		{
			printf("\n\t[ %s ]",tok[i].str);
			isInt=checkInt(tok[i]);				//checks if all of the str is digits, returns 1 if not int
			tok[i].num=isInt;					// assigns either 1 or 0 to struct value. 1= is not an int 0= is an int
				if(tok[i].num==15)				// ints are enum 9
					printf(" IS AN INT ENUM %d",tok[i].num);
					
				else							//if string contains any char other than int
					printf(" IS A LEX ERROR %d", tok[i].num);
		}
		else 
		{
			printf("\n\t[ %s ]",tok[i].str);
			isSym=checkSymbol(tok[i]);				//checks to see if token is any of the reserved characters
			tok[i].num=isSym;
				if(tok[i].num>16 && tok[i].num<32)		//reserve char are enum 10-21
					printf(" IS A SYMBOL ENUM %d", tok[i].num);
					
				else									//if not a aplha digit or symbol, its an error
					printf(" IS A LEX ERROR ENUM %d",tok[i].num);
		}
	}		
}	


int checkReserved(token tmp)
{
	

	int resWord=0;

	


	 if(strcasecmp(tmp.str,"BEGIN")==0)
		 resWord=1;
	 else if (strcasecmp(tmp.str,"END") ==0 ) 
		resWord=2;
	 else if (strcasecmp(tmp.str, "READ")==0)
		resWord=3;
	 else if (strcasecmp(tmp.str,"WRITE")==0 )
		resWord=4;
	 else if (strcasecmp(tmp.str,"IF") ==0) 
		resWord=5;
	 else if (strcasecmp(tmp.str,"THEN") ==0)
		resWord=6;
	 else if (strcasecmp(tmp.str,"ELSE") ==0)
		resWord=7;
	 else if (strcasecmp(tmp.str,"ENDIF")== 0)
		resWord=8;
	 else if (strcasecmp(tmp.str,"WHILE") ==0)
		resWord=9;
	 else if (strcasecmp(tmp.str,"ENDWHILE") ==0)
		resWord=10;
	 else if (strcasecmp(tmp.str,"GOTO") ==0)
		resWord=11;
	 else if (strcasecmp(tmp.str,"AND") ==0)
		resWord=12;
	 else if (strcasecmp(tmp.str,"OR") ==0)
		resWord=13;
	else if(strcasecmp(tmp.str,"NOT")==0)
		resWord=32;
	 
	 	 	
	else		
		resWord=14;
	 
	
	return resWord;

	
}

int checkInt(token tmp)
{
	
	int digit=15;
	extern int lexErrors;
	char *ptr;
	ptr= tmp.str;
	
	
	while(*ptr)
	{
		if(!isdigit(*ptr))				//dereferencing ptr and check if its a digit, if not give it enum 10 for lex error
		{
			digit=16;
		}
		
		ptr++;
	}
	if(digit==16)
		lexErrors++;
	return digit;
	
}
int checkSymbol(token tmp)
{
	
	int sym=0;
	extern int lexErrors;
	
	

	 if(strcmp(tmp.str,"(")==0)
		 sym=17;
	 else if (strcmp(tmp.str,")") ==0 ) 
		sym=18;
	 else if (strcmp(tmp.str, ";")==0)
		sym=19;
	 else if (strcmp(tmp.str,",")==0 )
		sym=20;
	 else if (strcmp(tmp.str,":=") ==0) 
		sym=21;
	 else if (strcmp(tmp.str,"+")== 0)
		sym=22;
	 else if (strcmp(tmp.str,"-") ==0)
		sym=23;
	else if(strcmp(tmp.str,"*") ==0)
		 sym=24;
	 else if(strcmp(tmp.str,"/") ==0)
		 sym=25;
	 else if(strcmp(tmp.str,"<") ==0)
		 sym=26;
	 else if(strcmp(tmp.str,"<=") ==0)    
		 sym=27;
	 else if(strcmp(tmp.str,">")==0)
		 sym=28;
	 else if(strcmp(tmp.str,">=") ==0)  
		 sym=29;
	 else if(strcmp(tmp.str,"=")==0)
		 sym=30;
	 else if(strcmp(tmp.str,"<>") ==0)
		 sym=31;

		 	
	else{						//if it does not its a lex error enumerated by 10
		sym=16;
		lexErrors++;
	}
		 
	
	return sym;
}

void printListing(int tokperline[])
{
	extern int counter;
	extern FILE *input;
	extern FILE *listing;
	extern FILE *output;
	extern int synErrors;
	extern int lexErrors;
	extern char inFile[MAX_CHAR];
	static int j =0,k=1,m=0;
	char lineBuff[MAXBUFF];
	clear_lineBuff(lineBuff);
	if(m==0)
		input=fopen(inFile,"r");
	extern int tokNum;
	if (counter == tokperline[j] || m==0 && counter<=tokNum)			//if its at the end of a line but not the end of the token list
		if (fgets(lineBuff,MAXBUFF,input)!=NULL)
		{
			fprintf(listing,"\n %d) %s",k,lineBuff);		//print it to the listing file
			k++;
			if(m!=0)
				j++;		//increment the line number
			
		}


		if(counter==tokNum-1)
		{ 
		fprintf(listing,"\n\nTotal Number Lexical Errors is %d", lexErrors);
		fprintf(listing,"\nTotal Number of Syntax Errors is %d\n",synErrors);		//if at the end of the token list print the total number of errors
			if(lexErrors ==0 && synErrors ==0)
				{ 
				fprintf(listing, "Program Compiled With No Errors");
				
				}
			else
				{ 
					fprintf(listing,"Program Could not be Compiled Due to %d Errors", synErrors+lexErrors);
					
				}
		}
	m++; 
}
void ParseTokens(token tok[],int tokperline[])			//this is the function that calls all of the other parsing functions to determine if the code is semantically correct
{
	extern int tokNum;
	extern FILE *input;
	extern FILE *listing;
	extern FILE *tmp;
	extern int counter;
	int j=0,k=0;
	int i=0;

	printListing(tokperline);
	i = BEGIN(listing, tok, i, tokperline);				//Begin function checks for the reserved word begin, it returns i which is used as an index for the struct array of tokens
	while(i<tokNum-1)							//while there are still tokens to evaluate
	{ 
		i=STMTLIST(listing,tok,i,tokperline);
	}
	END(listing, tok, i, tokperline);
	fclose(tmp);
}
int BEGIN(FILE *listing, token tok[],int i,int tokperline[])
{
extern int counter;
extern int synErrors;

	if (tok[i].num==1)    // If the token is Begin
	{
		i++;				//increment token and counter
		counter++;
		printListing( tokperline); // call printlisting to see whether to print the line BUff
	}		
	else
	{
		fprintf(listing, "\n Syntax Error: Expeted Begin");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);

	}
	return i;
	
	
}


int STMTLIST(FILE *listing,token tok[], int i, int tokperline[] )
{
extern int counter;
extern int synErrors;
extern int tokNum;
	if(tok[i].num== 3 || tok[i].num==4 || tok[i].num==5 || tok[i].num==9 || tok[i].num==14)
	{
		i=STMT(listing,tok,i,tokperline);
		if (tok[i].num == 3 || tok[i].num == 4 || tok[i].num == 5 || tok[i].num == 9 || tok[i].num == 14) // If the next token is a statement recursively call stmtlist
			i = STMTLIST(listing, tok, i, tokperline);
	}
	
	else 
	{
		fprintf(listing,"\n Syntax Error: Expected STMT or STMTLIST");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	return i;
	
}


int STMT(FILE *listing, token tok[], int i, int tokperline[])
{
extern int counter;
extern int synErrors;
	switch (tok[i].num)
	{
		case 3://If the token is read
				i++;
				counter++;
				printListing(tokperline);
				i=READ(listing,tok,i,tokperline);
				break;
		case 4://If the token is write
				i++;
				counter++;
				printListing(tokperline);
				i=WRITE(listing,tok,i,tokperline);
				break;
		case 5://If the token is IF
				i++;
				counter++;
				printListing( tokperline);
				i=IF(listing,tok,i,tokperline);
				break;
		case 9:// if the token is while
				i++;
				counter++;
				printListing(tokperline);
				i=WHILE( listing,tok,i,tokperline);
				break;
		case 14: //if the token is an ID
				i++;
				counter++;
				printListing(tokperline);
				i=ID( listing,tok,i,tokperline);
				break;
		default: // Else syntax error
				fprintf(listing,"\n Syntax Error: Expected Statement");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

				break;
		
	}
		
			return i;
			
}

int ID(FILE *listing, token tok[], int i, int tokperline[])
{
extern int counter;
extern int synErrors;
	if(tok[i].num== 21)  // If token is an assignment operator
	{
		i++;
		counter++;
		printListing( tokperline);
		i=EXPRESSION(listing,tok,i,tokperline);
		i=SEMI(listing,tok,i,tokperline);
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected Assignment Statement");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);

	}
	return i;
	return counter;
}

int READ(FILE *listing, token tok[], int i, int tokperline[])
{
extern int counter;
extern int synErrors;
	if (tok[i].num== 17)  // If the token is an open paran
		{
			i++;
			counter++;
			printListing( tokperline);
			i=IDLIST(listing,tok,i,tokperline);
			if(tok[i].num== 18)
				{
					i++;
					counter++;
					printListing( tokperline);
					i=SEMI(listing,tok,i,tokperline);
			
				}
				else
				{
					fprintf(listing,"\n Syntax Error: Expected Close Paranthesis");
					counter++;
					i++;
					synErrors++;
					printListing(tokperline);

				}

		}

	else
	{
	
		fprintf(listing,"\n Syntax Error: Expected Open Paranthesis");
		counter++;
		synErrors++;
		printListing(tokperline);

	}
		return i;
}

int WRITE(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if(tok[i].num==17)
	{
		i++;
		counter++;
		printListing( tokperline);
		i=EXPRESSION(listing,tok,i,tokperline);
			if(tok[i].num== 18)
			{
				i++;
				counter++;
				printListing( tokperline);
				i=SEMI( listing,tok,i,tokperline);
			}
			else
			{
				fprintf(listing,"\n Syntax Error: Expected Close Paranthesis");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

			}
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected Open Paranthesis");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);

	}
		return i;
}

int IF(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
		i=CONDITION(listing,tok,i,tokperline);
			if(tok[i].num== 6) // If the token is THEN
			{
				i++;
				counter++;
				printListing( tokperline);
				i=STMTLIST(listing,tok,i,tokperline);
					if(tok[i].num == 7) // if token is else
					{
						i++;
						counter++;
						printListing( tokperline);
						i=STMTLIST(listing, tok, i,tokperline);
		
					}
					if (tok[i].num == 8) // if token is endif
					{
						i++;
						counter++;
						printListing( tokperline);
					}
					else
					{
						fprintf(listing,"\n Syntax Error: Expected ENDIF");
						counter++;
						i++;
						synErrors++;
						printListing(tokperline);

					}

			}
			else
			{
				fprintf(listing,"\n Syntax Error: Expected THEN");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

			}
		return i;
}

int WHILE(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
		i=CONDITION(listing,tok,i,tokperline);
			if(tok[i].num == 10) // if endwhile
			{
				i++;
				counter++;
				printListing( tokperline);
			}
			else
			{
				fprintf(listing,"\n Syntax Error: Expected ENDWHILE");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);
			}
			return i;
	}
	


int IDLIST(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if(tok[i].num== 14)
	{
		i++;
		counter++;
		printListing( tokperline);
			if(tok[i].num == 20)
				i=IDLIST(listing,tok,i,tokperline);

		
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected ID List");	
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	return i;
}

int EXPRESSION(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if (tok[i].num == 17)
	{
		i++;
		counter++;
		printListing(tokperline);
			i=EXPRESSION(listing,tok,i,tokperline);
			if (tok[i].num == 18)
			{
				i++;
				counter++;
				printListing(tokperline);
				if (tok[i].num == 20)
				{
					i++;
					counter++;
						i=EXPRESSION(listing,tok,i,tokperline);
				}
			}
			else 
			{
				fprintf(listing,"\nSyntax Error: Expected Close Paranthesis");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

			}
	}
	else if(tok[i].num == 14 || tok[i].num == 15)
	{
		i++;
		counter++;
		printListing(tokperline);
		 if (tok[i].num > 21 && tok[i].num < 24)
		{
			gen_infix(tok,i, tokperline);
			i++;
			counter++;
			printListing(tokperline);
				i=EXPRESSION(listing,tok,i,tokperline);
		}
		
	}

	else
	{
		fprintf(listing,"\nSyntax Error: Expected Expression");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}

	return i;
}
int SEMI(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if(tok[i].num == 19)
	{
		i++;
		counter++;
		printListing( tokperline);
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected Semicolon");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	return i;
}
int CONDITION(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if(tok[i].num==17)
	{
		i++;
		counter++;
		printListing(tokperline);
		if ( tok[i].num == 14 || tok[i].num==15)	
		{ 
			i=NOTCOND( listing,tok,i,tokperline);
			if (tok[i].num == 18)
			{
				i++;
				counter++;
				printListing(tokperline);
			}
			else
			{
				fprintf(listing,"\n Syntax Error: Expected Close Paranthesis");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

			}
		}
		else
		{
			fprintf(listing,"\n Syntax Error: Expected Not Condition");
			counter++;
			i++;
			synErrors++;
			printListing(tokperline);
		}
		 if(tok[i].num== 12 || tok[i].num == 13)
		{
			i++;
			counter++;
			printListing( tokperline);
			i=NOTCOND(listing,tok,i,tokperline);
				if (tok[i].num == 18)
				{
					i++;
					counter++;
					printListing(tokperline);
				}
				else
				{
					fprintf(listing, "\n Syntax Error: Expected Close Paranthesis");
					counter++;
					i++;
					synErrors++;
					printListing(tokperline);
				}
		}

		
	}
	else if(tok[i].num == 32)
	{
		i=NOTCOND(listing, tok, i ,tokperline);
		if (tok[i].num == 18)
		{
			i++;
			counter++;
			printListing(tokperline);
		}
		else
		{
			fprintf(listing, "\n Syntax Error: Expected Close Paranthesis");
			counter++;
			i++;
			synErrors++;
			printListing(tokperline);

		}
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected Open Paranthesis");
		counter;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	return i;
}


int NOTCOND(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if(tok[i].num==32)
	{
		i++;
		counter++;
		printListing( tokperline);
			i=CONDITION(listing,tok,i,tokperline);
			if (tok[i].num == 18)
			{
				i++;
				counter++;
				printListing(tokperline);
			}
			else
			{
				fprintf(listing, "\n Syntax Error: Expected Close Paranthesis");
				counter++;
				i++;
				synErrors++;
				printListing(tokperline);

			}
	}
	
	else if(tok[i].num == 14 || tok[i].num == 15)
	{
		i=RELATECOND(listing, tok, i,tokperline);
	}
	else
	{
		fprintf(listing,"\n Syntax Error: Expected Either NOT (condition) or Relational Operator");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	
	return i;
}

int RELATECOND(FILE *listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if( tok[i].num == 14 || tok[i].num==15 )
	{
		i=EXPRESSION(listing,tok,i,tokperline);
				
		if(tok[i].num >25 && tok[i].num<32)
		{
			i++;
			counter++;
			printListing(tokperline);
			if ( tok[i].num == 14 || tok[i].num == 15)
				i=EXPRESSION(listing, tok, i, tokperline);
		}
		else 
		{
			fprintf(listing, "\n Syntax Error: Expected Relational Operator");
			counter++;
			i++;
			synErrors++;
			printListing(tokperline);
		}
	}
	else
	{
		fprintf(listing, "\n Syntax Error: Expected Expression");
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
	return i;
}

	
void END(FILE * listing, token tok[], int i, int tokperline[])
{
	extern int counter;
	extern int synErrors;
	if (tok[i].num==2)
	{
		i++;
		counter++;
		printListing( tokperline);
			
	} 
	else
	{
		fprintf(listing,"\n Syntax Error: Expected END");	
		counter++;
		i++;
		synErrors++;
		printListing(tokperline);
	}
}
	

void gen_infix(token tok[], int i, int tokperline[])    // generates intermediate code that is to be printed to the output file
{
	extern FILE *output;
	extern FILE *tmp;
	char temp[MAX_CHAR];
	static int j=1;
	memset(temp,'\0',MAX_CHAR);
	i--;
	fprintf(output,"int %s;\n",tok[i].str);
	strcat(temp, tok[i].str);
	i++;
	strcat(temp, tok[i].str);
	i++;
	fprintf(output,"int %s;\n", tok[i].str);
	strcat(temp,tok[i].str);
	fprintf(tmp,"Temp%d = %s\n",j,temp);
	i--;
	j++;
}
	
	
	
void appendFiles()			//reopens tmp file to move caret back to beginning, copies tmp file contents into output file
{
	extern FILE *tmp;
	extern FILE *output;
	extern int synErrors;
	extern int lexErrors;
	extern char tmpName[MAX_CHAR];
	char buffer[MAXBUFF];
	memset(buffer,'\0',MAXBUFF);
		tmp=fopen(tmpName,"r");
		while (fgets(buffer, MAXBUFF, tmp) != NULL)
			{
				fputs(buffer,output);
			}
		if ((lexErrors + synErrors) == 0)
		{
			fprintf(output,"Compilation Successful 0 Errors Found");
		}
		else
		{
			fprintf(output,"Compilation Failed %d Errors Found", synErrors+lexErrors);
		}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
