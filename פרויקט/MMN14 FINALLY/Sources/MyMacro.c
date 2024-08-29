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

boolean macroSpan(char* fileName, FILE* f, FILE* f_am)
{
	boolean flagPrint = TRUE;
	boolean macroFlag = FALSE;
	boolean call;
	boolean isOK = TRUE;
	int macroCounter = 0;
	int empty = 0;
	int row = 0;
	int i;
	char str1[MAX_SIZE];
	char str2[MAX_SIZE];
	char line[MAX_SIZE];
	macroList* m_head = NULL;
	macroList* m_node;
	macroList* node = NULL;
	while (fgets(line, MAX_SIZE - 1, f) != NULL) { /*read the next line*/
		row++;
		call = TRUE;
		if (emptyLine(line) == TRUE) { /*the line is empty line*/
			fprintf(f_am, "%s", line); /*prints the line to the target file*/
			empty++; /*counts the line*/
			continue;
		}
		if (longLine(line) == TRUE) { /*the line is too long - ERROR*/
			printerrors(fileName, LONG_LINE, row, line);
			isOK = FALSE;
			continue;
		}
		sscanf(line, "%s %s", str1, str2); /*read the next 2 words*/
		if (!strcmp(str1, "endmacr")) { /*the line is end macro line*/
			macroCounter = 0;
			flagPrint = TRUE;
			macroFlag = FALSE;
			node->next = m_head;
			m_head = node;
			continue;
		}
		if (macroFlag == TRUE) { /*the line is inside macro*/
			node->numOfLines++;
			strcpy(node->macroLines[macroCounter], line);
			macroCounter++;
			continue;
		}
		m_node = m_head;
		while (m_node != NULL) { /*go throw the macro list*/
			if (!strcmp(str1, (m_node->name))) { /*the line is a calling to macro*/
				call = FALSE;
				for (i = 0; i < (m_node->numOfLines); i++) /*print to the target file the macro node*/
					fprintf(f_am, "%s", (m_node->macroLines[i]));
			}
			m_node = m_node->next;
		}
		if (!strcmp(str1, "macr")) { /*the line is a start macro line*/
			node = allocationMacroList(); /*allocation place to macroList list*/
			node->numOfLines = 0;
			node->next = NULL;
			strcpy(node->name, str2);
			flagPrint = FALSE;
			macroFlag = TRUE;
			continue;
		}
		if (flagPrint == TRUE && call == TRUE) /*if the line has to be printed - print it to the target file.*/
			fprintf(f_am, "%s", line);
	}
	freeMacroList(m_head);
	if (empty == row) { /*if the file is an empty file step to the next file.*/
		printerrors(fileName, EMPTY_FILE, 0, "");
		return 0;
	}
	return isOK;
}

