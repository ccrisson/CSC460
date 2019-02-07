
#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#define MAX_CHAR 30 

int i=0, cont=0, inExist=0,outExist=1,ext=0,again=0;
char inFile [MAX_CHAR], outFile[MAX_CHAR],outBak[MAX_CHAR],c=NULL,choice=NULL;
FILE *input,*output,*outbak,*list;

void getInFile(int,int,int); 
void getOutFile(int,int,int,char,char,char,char); 
void closeFiles(); 

void closeFiles() {
	
	fclose(input);     
    fclose(output);
    fclose(list);
}

#endif
