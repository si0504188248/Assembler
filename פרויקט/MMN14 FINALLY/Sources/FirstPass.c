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


int firstTrans(char* fileName, FILE* f_am, char* registers[], char* asterisk_registers[])
{

	int row = 1;
	int end = 0;
	int errorFlag = 0;
	int column = 0;
	char line[MAX_SIZE];

	while (fgets(line, MAX_SIZE, f_am) != NULL) {
		column = whiteSpace(line, 0); /*go to the next char that not space.*/
		if (line[column] == ';') { /*check if the line is a comment line.*/
			row++;
			continue;
		}
		if (emptyLine(line) == TRUE) { /*check if the line is an empty line.*/
			row++;
			continue;
		}
		end = first(fileName, line, row, registers, asterisk_registers);
		if (end) /*if there is an error in this line, count the error.*/
			errorFlag++;
		row++;
	}
	end = checkEntryExtern(fileName, row); /*check if there are entry and extern label*/
	if (end)
		errorFlag++;
	return errorFlag;
}


int first(char* fileName, char* line, int row, char* registers[], char* asterisk_registers[])
{
	int column = 0;
	int isDirective;
	int dataCounter = 0;
	int opcode;
	int isOK = 0;
	int label;
	int i = 1;
	int k;
	char word1[MAX_SIZE];
	/*char* word2 = NULL;*/
	boolean flagWord = FALSE;
	boolean dataFlag = FALSE;
	boolean flag = FALSE;
	symbolTabel* st_node = NULL;
	while (line[i - 1] != '\n') {
		if (line[i] == ':' && !isspace(line[i + 1])) {
			printerrors(fileName, LABEL_SPACE, row, "");
			return 1;
		}
		if (line[i] == ':')
		{
			k = i + 1;
			while (line[k] != '\n')
			{
				if (!isspace(line[k++]))
					flag = TRUE;
			}
			if (flag == FALSE) {
				printerrors(fileName, LABEL_EMPTY_LINE, row, "");
				return 1;
			}
		}
		i++;
	}

	column = whiteSpace(line, column);
	column += nextWord(line, column, word1);
	label = isLabel(fileName, word1, 1, row, registers, asterisk_registers);

	if (label == 2) {

		return 1;
	}
	if (label == 1)
	{ /*a declaration of label.*/
		/*word2=nextWord(line, word2, column);
	 if(word2==NULL)
		  {
		  printerrors(fileName, LABEL_SPACE, row, "");
	  return 1;
  }*/
		flagWord = TRUE;

		isOK = checkLabelLine(fileName, line, word1, row, column, registers, asterisk_registers);
		if (isOK == 2) {
			return 0;
		}
		if (isOK == 1) {

			return 1;
		}

	}
	else if ((isDirective = directive(word1)) != NONE) {
		/*first word is not a label*/
		flagWord = TRUE;
		if (isDirective == ENTRY) {
			isOK = isEntry(fileName, column, line, 0, registers, asterisk_registers, row);

			if (isOK)
				return isOK;
			return 0;
		}
		if (isDirective == EXTERN) {
			isOK = isExtern(fileName, column, line, 0, registers, asterisk_registers, row);

			if (isOK)
				return isOK;
			return 0;
		}
		if (isDirective == DATA) {

			dataCounter = isData(fileName, line, row, column);
			if (!dataCounter) {
				printerrors(fileName, ILLEGAL_DATA, row, "");
				return 1;
			}
		}
		if (isDirective == STRING)
			dataCounter = isString(fileName, line, row, column);
		if (isOK) {

			return 1;
		}

		g->DC += dataCounter; /*increase DC the length of data line.*/
		st_node = g->st_head;
		while (st_node != NULL) { /*look for first "data" label*/
			if (!strcmp(st_node->attributes, "data")) {
				dataFlag = TRUE;
				st_node->value += dataCounter;
				break;
			}
			st_node = st_node->next;
		}
		if (dataFlag == FALSE) /*No data lines, add to DCF the value of data.*/
			g->DCF += dataCounter;
	}
	else if ((opcode = actions(word1)) > -1) { /*an action.*/
		flagWord = TRUE;
		if (checkActionLine(fileName, 1, line, opcode, column, row, registers, asterisk_registers)) {
			return 1;
		}
		g->IC += g->L; /*increase IC the amount of information words.*/
		g->L = 0;
	}

	if (flagWord == FALSE) {
		/*incorrect line - ERROR*/
		if (word1[0] == '.') {
			printerrors(fileName, ILLEGAL_DIRECTIVE, row, word1);
			isOK = 1;
		}
		else {
			printerrors(fileName, ILLEGAL_COMMAND, row, word1);
			isOK = 1;
		}
	}
	return isOK;
}



int isExtern(char* fileName, int column, char* line, int declare, char* registers[], char* asterisk_registers[], int row)
{
	char word2[MAX_SIZE];
	int label = 0;
	symbolTabel* node = NULL;
	symbolTabel* st_node = NULL;
	entryList* ent_node = NULL;
	column = whiteSpace(line, column);
	column += nextWord(line, column, word2);
	if (strlen(word2) == 0) { /*No label - ERROR*/
		printerrors(fileName, ILLEGAL_LINE, row, line);
		return 1;
	}
	label = isLabel(fileName, word2, declare, row, registers, asterisk_registers);
	if (label == 2) {
		printerrors(fileName, ILLEGAL_LABEL, row, word2);
		return 1;
	}
	if (label == 1) { /*A label*/
		st_node = g->st_head;
		while (st_node != NULL) { /*check it didn't defined as a regular label*/
			if (!strcmp((st_node->symbol), word2)) {
				if (!strcmp(st_node->attributes, "external")) {
					printerrors(fileName, WARNING_EXTERN, row, word2);
					return 0;
				}
				printerrors(fileName, EXTERN_DEFINE, row, word2);
				return 1;
			}
			st_node = st_node->next;
		}
		ent_node = g->ent_head;
		while (ent_node != NULL) { /*check it didn't defined as an entry label*/
			if (!strcmp((ent_node->label), word2)) {
				printerrors(fileName, ENTRY_EXTERN, row, word2);
				return 1;
			}
			ent_node = ent_node->next;
		}
		node = allocationSymbolTabelList(node); /*the label is O.k*/
		g->st_head = addContentToSymbolTabelNode(node, word2, 0, "external");
	}
	else {
		printerrors(fileName, ILLEGAL_LABEL, row, word2); /*Not a label - ERROR*/
		return 1;
	}
	return 0;
}

int checkLabelLine(char* fileName, char* line, char* word1, int row, int column, char* registers[], char* asterisk_registers[])
{
	int isOK = 0;
	int dataCounter = 0;
	int opcode;
	int value;
	int isDirective;
	char word2[MAX_SIZE];
	char* attributes2 = NULL;
	char* attributes = NULL;
	boolean flagWord = FALSE;
	symbolTabel* node = NULL;
	symbolTabel* st_node = NULL;
	entryList* ent_node = NULL;
	externList* ext_node = NULL;
	st_node = g->st_head;
	while (st_node != NULL) { /*declared already - ERROR.*/
		strtok(word1, ":");
		if (!strcmp((st_node->symbol), word1)) {
			printerrors(fileName, LABEL_TWICE, row, word1);
			return 1;
		}
		strcat(word1, ":");
		st_node = st_node->next;
	}
	ent_node = g->ent_head;
	while (ent_node != NULL) { /*an entry label.*/
		strtok(word1, ":");
		if (word1 != NULL && !strcmp(word1, ent_node->label)) {
			attributes2 = allocationWord(ENTRY_SIZE);
			strcpy(attributes2, "entry");
		}
		strcat(word1, ":");
		ent_node = ent_node->next;
	}
	ext_node = g->ext_head;
	while (ext_node != NULL) { /*extern label - ERROR.*/
		strtok(word1, ":");
		if (word1 != NULL && !strcmp(word1, ext_node->label)) {
			printerrors(fileName, EXTERN_DEFINE, row, word1);
			return 1;
		}
		strcat(word1, ":");
		ext_node = ext_node->next;
	}
	column = whiteSpace(line, column);
	column += nextWord(line, column, word2);
	if ((isDirective = directive(word2)) != NONE) {
		flagWord = TRUE;
		if (isDirective == ENTRY) {
			printerrors(fileName, WARNING_LABEL, row, line);
			isOK = isEntry(fileName, column, line, 0, registers, asterisk_registers, row);
			if (isOK)
				return isOK;
			return 2;
		}
		else if (isDirective == EXTERN) {
			printerrors(fileName, WARNING_LABEL, row, line);
			isOK = isExtern(fileName, column, line, 0, registers, asterisk_registers, row);
			if (isOK)
				return isOK;
			return 2;
		}
		else if (isDirective == STRING) {
			dataCounter = isString(fileName, line, row, column);
			attributes = allocationWord(DATA_SIZE);
			strcpy(attributes, "data");
			value = dataCounter;
		}
		else if (isDirective == DATA) {
			dataCounter = isData(fileName, line, row, column);
			if (dataCounter < 1) {
				printerrors(fileName, ILLEGAL_DATA, row, "");
				return 1;
			}
			attributes = allocationWord(DATA_SIZE);
			strcpy(attributes, "data");
			value = dataCounter;
		}
	}
	else if ((opcode = actions(word2)) > -1) { /*an action.*/
		flagWord = TRUE;
		if (checkActionLine(fileName, 1, line, opcode, column, row, registers, asterisk_registers))
			return 1;
		attributes = allocationWord(CODE_SIZE);
		strcpy(attributes, "code");
		value = g->IC;
	}
	if (attributes != NULL && !strcmp(attributes, "data") && g->DCF) { /*label is "data" label.*/
		value += g->DCF;
		g->DCF = 0;
	}
	node = allocationSymbolTabelList(node);
	g->st_head = addContentToSymbolTabelNode(node, word1, value, attributes);
	if (attributes2 != NULL && !strcmp(attributes2, "entry")) /*entry label.*/
		strcpy(g->st_head->attributes2, attributes2);
	g->DC += dataCounter; /*increase DC in the length of data.*/
	g->IC += g->L; /*increase IC with L (L updates in code file)*/
	g->L = 0;
	if (flagWord == FALSE) { /*incorrect line - ERROR*/
		printerrors(fileName, ILLEGAL_LINE, row, line);
		return 1;
	}
	return isOK;
}


int isEntry(char* fileName, int column, char* line, int declare, char* registers[], char* asterisk_registers[], int row)
{
	char word[MAX_SIZE];
	int label = 0;
	symbolTabel* st_node = NULL;
	entryList* ent_node = NULL;
	column = whiteSpace(line, column);
	column += nextWord(line, column, word);
	if (strlen(word) == 0) { /*No label - ERROR*/
		printerrors(fileName, ILLEGAL_LINE, row, line);
		return 1;
	}
	label = isLabel(fileName, word, declare, row, registers, asterisk_registers);
	if (label == 2)
		return 1;
	if (label == 1) { /*A label*/
		st_node = g->st_head;
		while (st_node != NULL) {
			if (!strcmp((st_node->symbol), word))
				strcpy(st_node->attributes2, "entry");
			st_node = st_node->next;
		}
		ent_node = g->ent_head;
		while (ent_node != NULL) {
			if (!strcmp(ent_node->label, word)) {
				printerrors(fileName, WARNING_ENTRY, row, word);
				return 0;
			}
			ent_node = ent_node->next;
		}
		ent_node = allocationEntryList(ent_node); /*enter the label to the entryList*/
		g->ent_head = addContentToEntryNode(ent_node, word, row);
	}
	else {
		printerrors(fileName, ILLEGAL_LABEL, row, word); /*Not a label - ERROR*/
		return 1;
	}
	return 0;
}

int checkActionLine(char* fileName, int trans, char* line, int opcode, int column, int row, char* registers[], char* asterisk_registers[])
{
	int isOK = 0;
	if (opcode >= MOV && opcode <= LEA)
		isOK = operand2(fileName, line, column, trans, opcode, row, registers, asterisk_registers);
	if (opcode >= CLR && opcode <= JSR)
		isOK = operand1(fileName, line, column, trans, opcode, row, registers, asterisk_registers);
	if (opcode == RTS || opcode == STOP)
		isOK = operand0(fileName, line, column, trans, row, opcode);
	return isOK;
}
