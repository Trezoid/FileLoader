/*
 * File read header made by Liam Davis (u305769)
 */

#include <stdio.h>
#include <string.h>

/*
 * reads in the file, returns a string containing all contents of the file.
 */
char* readFile(char* fileName)
{	
	FILE *f;
       
	f = fopen(fileName, "r");
	int i;
	int n = 0, b; while((b=fgetc(f)) != EOF) n+=(b==10)?1:0;fseek(f,0,SEEK_SET);
	char* c;
	char buffer[1024];
	char huge[(1024 * n)];
	c = huge;
	if(f == NULL)
	{
		return "File Not Found";
	}

	fgets(buffer, 100, f);
	strcpy(c, buffer);
	i = 0;
	while(i+1 <= n)
	{
		fgets(buffer,100, f);
		strcat(c, buffer);
		i++;
	}
	fseek(f, 0, SEEK_SET);
	fclose(f);
	return c;
}
/*
 * takes in input in the form "fileName#fileContent" and then completely overwrites the file with that content
 */

int writeFile(char* fileName, char* content)
{
	char outCont[strlen(content)+ 10];
	strcpy(outCont, content);
	FILE *f;
	f = fopen(fileName, "w");
	
	if(f == NULL)
	{
		return 0;
	}
	int i;
	
	for(i = 0; i < (strlen(outCont) + 1); i++)
	{
		fputc(outCont[i], f);
	}
	fclose(f);
	return 1;
}
/*
 * takes input in the form "FileName#lineNumber#newLine" and overwrites that line or the last line of the file if that line doesn't exit.
 */

int writeLine(char* fileName, int lineNum, char* newLine)
{
	char *result;
	char *fileIn = readFile(fileName);
	char fileSplit[strlen(fileIn)+ 10];
	strcpy(fileSplit, fileIn);
	int i;
	char outFile[strlen(fileSplit) + strlen(newLine) + 100];
	char *newDelim = "\n";
	
	result = strtok(fileSplit, newDelim);
	
	if(lineNum > 0)
	{
		strcpy(outFile, result);
		strcat(outFile, "\n");

		for(i = 1; i < lineNum; i++)
		{
			result = strtok(NULL, newDelim);
			strcat(outFile, result);
			strcat(outFile, "\n");
		}
		result = strtok(NULL, newDelim);
		strcat(outFile, newLine);
		strcat(outFile, "\n");
	}
	else
	{
		strcpy(outFile, newLine);
		strcat(outFile, "\n");
	}
	while(result != NULL)
	{
		char prevResult[500];
		strcpy(prevResult, result);
		result = strtok(NULL, newDelim);
		if(result != NULL && strcmp(prevResult, result) != 0)
		{ 
			strcat(outFile, result);
			strcat(outFile, "\n");
		}
	}
	int e = writeFile(fileName, outFile);
return e;
}

char* findLine(char* fileName, char* searchString)
{
	char* fileIn = readFile(fileName);
	char* newDelim = "\n";
	char *fileSplit;
	fileSplit = strtok(fileIn, newDelim);
	if(strstr(fileSplit, searchString) > 0)
	{
		return fileSplit;
	}
	else{
		while(fileSplit != NULL)
		{	
			fileSplit = strtok(NULL, newDelim);
			if(strstr(fileSplit, searchString) > 0)
			{
				return fileSplit;
			}
		}
	}
	return "string not found";
}

int findLineNumber(char* fileName, char* searchString)
{
	char* result;
	char *fileIn = readFile(fileName);
	char *newDelim = "\n";
	int lineNum = 0;
	result = strtok(fileIn, newDelim);
	if(strstr(result, searchString) != NULL)
	{
		return 0;
	}
	else{
		while(result != NULL)
		{	
			lineNum++;
			result = strtok(NULL, newDelim);
			if(strstr(result, searchString) != NULL)
			{
				return lineNum;
			}
		}
	}
	return -1;
}

char* findAllLine(char* fileName, char* searchString)
{
	char* fileIn = readFile(fileName);
	char* newDelim = "\n";
	char totalLines[strlen(fileIn) + 200];
	char* fileSplit;
	fileSplit = strtok(fileIn, newDelim);
	if(strstr(fileSplit, searchString) > 0)
	{
		strcpy(totalLines, fileSplit);
		strcat(totalLines, "\n");
	}
	int i;
	while(1)
	{	
		fileSplit = strtok(NULL, newDelim);
		if(fileSplit == NULL)
		{
			break;
		}
		else if(strstr(fileSplit, searchString) > 0)
		{
			 strcat(totalLines, fileSplit);
			 strcat(totalLines, "\n");
		}
		
	}
	char* output;
	output = totalLines;
	if(strlen(totalLines) > 0)
	{
		return output;
	}
	else{
		return "No Lines Found";
	}
}

