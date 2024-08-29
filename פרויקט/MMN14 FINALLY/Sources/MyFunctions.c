#define _CRT_SECURE_NO_WARNINGS
#include "MyDataBase.h"
#include "MyDefine.h"
#include "FirstPass.h"
#include "MyFunctions.h"
#include "MyListFunctions.h"
#include "MyData.h"
#include "MyCode.h"
#include "MyPrint.h"
#include "SecondPass.h"
#include "MyMacro.h"

int whiteSpace(char* line, int i)
{
	while (isspace(line[i]) && line[i] != '\n')
		i++;
	return i;
}


int nextWord(char* line, int column, char* word)
{
	int index = strcspn(line + column, " \t\n\v\f\r");
	strncpy(word, line + column, index);
	word[index] = '\0';
	return index;
}

boolean longLine(char* line)
{
	int i = 0;
	while (line[i] != '\n')
		i++;
	i++;
	if (i > (MAX_SIZE - 3))
		return TRUE;
	return FALSE;
}

int actions(char* word)
{
	int i;
	for (i = 0; i < ACTION_NUMBER; i++) {
		if (!strcmp(word, actArr[i].name))
		{
			return actArr[i].opcode;
		}
	}
	return -1;
}

/*this function checks if a specific word is a directive word. if so, the function returns the number of the directive, else return -1.*/
directiveType directive(char* word)
{
	int flag = -1;
	char* directiveArr[4] = {
	  ".data"   ,
	  ".string" ,
	  ".entry"  ,
	  ".extern"
	};
	int i;
	for (i = 0; i < 4; i++)
		if (!strcmp(word, directiveArr[i]))
			flag = i;
	switch (flag) {
	case 0:
		return DATA;
	case 1:
		return STRING;
	case 2:
		return ENTRY;
	case 3:
		return EXTERN;
	}
	return NONE;
}

/*this function gets a line tnd checks if it is an empty line. if so, the function returns 1 else 0*/
boolean emptyLine(char* line)
{
	int i = 0;
	while (line[i] != '\n') {
		if (!isspace(line[i++]))
			return FALSE;
	}
	return TRUE;
}

int isLabel(char* fileName, char* word, int declare, int row, char* registers[], char* asterisk_registers[])
{

	int i = 0, j;
	char* directiveArr[4] = {
	  "data"   ,
	  "string" ,
	  "entry"  ,
	  "extern"
	};
	if (declare) {
		i = 2;
		if (word[strlen(word) - 1] != ':') /*a declaration must finish with ':'*/
			return 0;
		strtok(word, ":");
	}
	if (!isalpha(word[0])) { /*The first char of the label has to be letter*/
		if (declare)
			printerrors(fileName, FIRST_LETTER, row, word);
		return i;
	}
	if (strlen(word) >= LABEL_SIZE) { /*a label can't be more than 32 chars*/
		if (declare)
			printerrors(fileName, LONG_LABEL, row, word);
		return i;
	}
	if (!strcmp(word, "macr") || !strcmp(word, "endmacr")) {/*can't be reserved word*/
		if (declare)
			printerrors(fileName, RESERVED_WORD, row, word);
		return i;
	}
	for (j = 0; j < ACTION_NUMBER; j++) { /*a label can't be reserved word*/
		if (!strcmp(word, actArr[j].name)) {
			if (declare)
				printerrors(fileName, RESERVED_WORD, row, word);
			return i;
		}
	}
	for (j = 0; j < 4; j++) { /*a label can't be reserved word*/
		if (!strcmp(word, directiveArr[j])) {
			if (declare)
				printerrors(fileName, RESERVED_WORD, row, word);
			return i;
		}
	}
	for (j = 0; j < REGISTER_NUMBER; j++) { /*a label can't be reserved word*/
		if (!strcmp(word, registers[j]) || !strcmp(word, asterisk_registers[j])) {
			if (declare)
				printerrors(fileName, RESERVED_WORD, row, word);
			return i;
		}
	}
	for (j = 1; j < strlen(word); j++) { /*a label can contain just letters and numbers*/
		if (!isalnum(word[j])) {
			if (declare)
				printerrors(fileName, ALPHANUMERIC_LABEL, row, word);
			return i;
		}
	}
	return 1;
}


char* allocationWord(int size)
{
	char* word = (char*)malloc(size);
	if (word == NULL) {
		printf("Failed to allocate space to word. exiting.\n");
		exit(1);
	}
	return word;
}

