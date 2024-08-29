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


int secondTrans(char* fileName, FILE* f_am, char* registers[], char* asterisk_registers[])
{
	int row = 1;
	int end = 0;
	int errorFlag = 0;
	int labelRow = 0;
	int column = 0;
	char line[MAX_SIZE];
	char word[LABEL_SIZE];
	boolean found;
	entryList* ent_node = NULL;
	symbolTabel* st_node = NULL;
	ent_node = g->ent_head;
	while (ent_node != NULL) { /*check if there is a label defined as .entry label, and in practice didn't declared.*/
		found = FALSE;
		st_node = g->st_head;
		strcpy(word, ent_node->label);
		labelRow = ent_node->row;
		while (st_node != NULL) {
			if (!strcmp(ent_node->label, st_node->symbol))
				found = TRUE;
			st_node = st_node->next;
		}
		if (found == FALSE) {
			printerrors(fileName, JUST_ENTRY, labelRow, word);
			return 1;
		}
		ent_node = ent_node->next;
	}
	while (fgets(line, MAX_SIZE - 1, f_am) != NULL) {
		column = whiteSpace(line, column); /*go to the next char that not space.*/
		if (line[column] == ';') { /*check if the line is a comment line.*/
			row++;
			continue;
		}
		if (emptyLine(line) == TRUE) { /*check if the line is an empty line.*/
			row++;
			continue;
		}
		end = second(fileName, line, row, registers, asterisk_registers); /*sends the line to "second" function.*/
		if (end) /*there is an error in this line, count the error.*/
			errorFlag++;
		row++;
	}
	return errorFlag;
}


int second(char* fileName, char* line, int row, char* registers[], char* asterisk_registers[])
{
	int column = 0;
	int isOK = 0;
	int opcode = 0;
	char word1[MAX_SIZE];
	char word2[MAX_SIZE];
	symbolTabel* st_node = NULL;
	entryList* ent_node = NULL;
	column = whiteSpace(line, column);
	column += nextWord(line, column, word1);
	if (isLabel(fileName, word1, 1, row, registers, asterisk_registers) == TRUE) { /*if the word is a declaration of label.*/
		ent_node = g->ent_head;
		st_node = g->st_head;
		strtok(word1, ":");
		while (st_node != NULL) { /*find the label in the symbolTabel*/
			if (!strcmp(st_node->symbol, word1))
				break;
			st_node = st_node->next;
		}
		if (st_node == NULL) /*the label is a label before .extern ro .entry label, ignoring.*/
			return 0;
		while (ent_node != NULL) {
			if (!strcmp(ent_node->label, st_node->symbol)) {
			}
			ent_node = ent_node->next;
		}
		column = whiteSpace(line, column);
		column += nextWord(line, column, word2);
		opcode = actions(word2);
		isOK += checkActionLine(fileName, 2, line, opcode, column, row, registers, asterisk_registers);
	}
	else { /*not a label*/

		opcode = actions(word1);
		isOK += checkActionLine(fileName, 2, line, opcode, column, row, registers, asterisk_registers);
	}
	return isOK;
}
