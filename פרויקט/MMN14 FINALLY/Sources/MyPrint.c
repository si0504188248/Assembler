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


int printfiles(char* fileName)
{

	FILE* f_ent;
	FILE* f_ob;
	FILE* f_ext;
	int i;
	/*int move;*/

	char ob_file_name[MAX_SIZE] = { 0 };
	char ent_file_name[MAX_SIZE] = { 0 };
	char ext_file_name[MAX_SIZE] = { 0 };
	/*entryList* ent_node = NULL;*/
	externList* ext_node = NULL;
	symbolTabel* sb_table = NULL;

	strcpy(ob_file_name, fileName);
	strcat(ob_file_name, ".ob");
	strcpy(ent_file_name, fileName);
	strcat(ent_file_name, ".ent");
	strcpy(ext_file_name, fileName);
	strcat(ext_file_name, ".ext");

	f_ob = fopen(ob_file_name, "w+"); /*create ".ob" file*/
	fprintf(f_ob, "\t%d %d\n", g->IC - START_IC, g->DC); /*print the title to the file (IC and DC)*/
	for (i = 0; i < (g->IC - START_IC); i++) { /*print the code .*/

		fprintf(f_ob, "%.4d ", (i + START_IC));
		fprintf(f_ob, "%05o\n", g->code[i]);
		fprintf(f_ob, "\n");

	}
	for (i = 0; i < g->DC; i++) { /*print the data */

		fprintf(f_ob, "%.4d ", (i + g->IC));

		fprintf(f_ob, "%05o\n", g->data[i]);

		fprintf(f_ob, "\n");
	}
	fclose(f_ob);

	g->st_head = reverseSymbolTabelList();
	sb_table = g->st_head;
	if (sb_table != NULL)
	{
		f_ent = fopen(ent_file_name, "w+");
		while (sb_table != NULL)
		{ /*there are entry labels - print them to".ent" file*/
			if (!strcmp(sb_table->attributes2, "entry"))
				fprintf(f_ent, "%s   %d\n", sb_table->symbol, sb_table->value);
			sb_table = sb_table->next;
		}
		fclose(f_ent);
	}


	g->ext_head = reverseExternList();
	ext_node = g->ext_head;
	g->st_head = reverseSymbolTabelList();
	sb_table = g->st_head;
	if (ext_node != NULL)
	{

		f_ext = fopen(ext_file_name, "w+");
		while (ext_node != NULL) { /*there are extern labels - print them to ".ext" file*/
			fprintf(f_ext, "%s   %.4d\n", ext_node->label, ext_node->address);
			ext_node = ext_node->next;

		}
		fclose(f_ext);
	}

	return 0;
}



/*This function prints all the errors*/
int printerrors(char* fileName, int flag, int row, char* word)
{
	word = strtok(word, "\n");
	switch (flag) {
	case NO_FILE:
		printf("No files. exit.\n");
		break;
	case ILLEGAL_COMMAND:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name of command.\n", fileName, row, word);
		break;
	case ILLEGAL_DIRECTIVE:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name of directive.\n", fileName, row, word);
		break;
	case EMPTY_FILE:
		printf("\"%s\" file is empty file.\n", fileName);
		break;
	case LABEL_SPACE:
		printf("ERROR: in \"%s\" file: line %d: after label must be a space.\n", fileName, row);
		break;
	case WARNING_EXTERN:
		printf("WARNING: in \"%s\" file: line %d: label \"%s\" already declared as .extern label. ignoring the statement.\n", fileName, row, word);
		break;
	case WARNING_ENTRY:
		printf("WARNING: in \"%s\" file: line %d: label \"%s\" already declared as .entry label. ignoring the statement.\n", fileName, row, word);
		break;
	case COMMA:
		printf("ERROR: in \"%s\" file: line %d: ',' not in place.\n", fileName, row);
		break;
	case MANY_OP:
		printf("ERROR: in \"%s\" file: line %d: too much arguments.\n", fileName, row);
		break;
	case ILLEGAL_LINE:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal line.\n", fileName, row, word);
		break;
	case WORNG_FILE:
		printf("ERROR: can't find \"%s\" file. continue to next file.\n", fileName);
		break;
	case ILLEGAL_DATA:
		printf("ERROR: in \"%s\" file: line %d: illegal data line.\n", fileName, row);
		break;
	case ILLEGAL_STRING:
		printf("ERROR: in \"%s\" file: line %d: illegal string line.\n", fileName, row);
		break;
	case FIRST_LETTER:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name for label. the first character in a label must be a letter.\n", fileName, row, word);
		break;
	case ALPHANUMERIC_LABEL:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name for label. a label must contain alphanumeric characters only.\n", fileName, row, word);
		break;
	case ILLEGAL_LABEL:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name for label.\n", fileName, row, word);
		break;
	case RESERVED_WORD:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name for label. a label can't be a reserved word.\n", fileName, row, word);
		break;
	case LONG_LABEL:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal name for label. a label can't contains more than 32 characters.\n", fileName, row, word);
		break;
	case NO_MEMMORY:
		printf("ERROR: no memmory for \"%s\" file. Passes to the next file\n", fileName);
		break;
	case ILLEGAL_NUMBER:
		printf("ERROR: in \"%s\" file: line %d: the number is not in the range of the possible numbers.\n", fileName, row);
		break;
	case NO_OPERAND2:
		printf("ERROR: in \"%s\" file: line %d: excepted 2 arguments.\n", fileName, row);
		break;
	case NO_OPERAND1:
		printf("ERROR: in \"%s\" file: line %d: excepted 1 argument.\n", fileName, row);
		break;
	case LABEL_NOT_FOUND:
		printf("ERROR: in \"%s\" file: line %d: label \"%s\" not found.\n", fileName, row, word);
		break;
	case ILLEGAL_OPERAND:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" illegal operand.\n", fileName, row, word);
		break;
	case NOT_COMMA:
		printf("ERROR: in \"%s\" file: line %d: there is no ',' between the arguments.\n", fileName, row);
		break;
	case LABEL_TWICE:
		printf("ERROR: in \"%s\" file: line %d: \"%s\" label declared already.\n", fileName, row, word);
		break;
	case LONG_LINE:
		printf("ERROR: in \"%s\" file: line %d: line can't contain more than 80 characters.\n", fileName, row);
		break;
	case ERROR_IN_FILE:
		printf("%d ERRORS in \"%s\" file. Can't create \"%s.ob\" file. exit.\n\n", row, word, word);
		break;
	case EXTERN_DEFINE:
		printf("ERROR: in \"%s\" file: line %d: label \"%s\" already defined as extern label.\n", fileName, row, word);
		break;
	case ENTRY_EXTERN:
		printf("ERROR: in \"%s\" file: line %d: label \"%s\" defined as .entry and as .extern.\n", fileName, row, word);
		break;
	case ILLEGAL_SOURCE:
		break;
	case ILLEGAL_TARGET:
		printf("ERROR: in \"%s\" file: line %d: target operand - \"%s\" illegal to this command.\n", fileName, row, word);
		break;
	case WARNING_LABEL:
		printf("WARNING: in \"%s\" file: in line %d: a label before .entry or .extern directive. ignoring the label.\n", fileName, row);
		break;
	case JUST_ENTRY:
		printf("ERROR: in \"%s\" file: line %d: label \"%s\" declared as .entry but did not defined.\n", fileName, row, word);
		break;
	case ILLEGAL_REGIST:
		printf("ERROR: in \"%s\" file: line %d: illegal \"%s\" register.\n", fileName, row, word);
		break;
	case LABEL_EMPTY_LINE:
		printf("ERROR: in \"%s\" file: line %d: content of label must be in the statement line.\n", fileName, row);
		break;
	}
	return 0;
}
