/*Program1
  file_util.h
  CSC-460 Language Translation
  Group 9
  Chris Crisson CRI4537@calu.edu
  Matthew Bedillion BED9714@calu.edu
  Mark Blatnik BLA9072@calu.edu
  Adlene Bellaoucha BEL7984@calu.edu
*/
#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#define MAX_CHAR 50
#define INEXT ".IN"
#define OUTEXT ".OUT"
#define BACKEXT ".BAK"
#define LISTEXT ".LIS"
#define TEMPFILENAME "temporary.TEMP"

FILE *inFile;
FILE *outFile;
extern int go;
extern int overwrite;

int i;
char inputFilename[MAX_CHAR];
char outputFilename[MAX_CHAR];
char choice[MAX_CHAR];
char inExtention[MAX_CHAR];
char outExtention[MAX_CHAR];

char* getInFile(char* file);
char* getOutFile(char* file, char* defaultName);
int copyFile(char* in, char* out);
void backupFile(char* file);
void createListingFile(char* file);
void createTempFile();
void removeTempFile();

#endif