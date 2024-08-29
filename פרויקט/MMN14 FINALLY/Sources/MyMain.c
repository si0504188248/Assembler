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


/*					*The Project*
This program is an assembler for an imaginary computer.
it gets an assembler files (".as" ending) in the command line, it checks the file - to see there are no erros and then makes the required files (".ob" ending. And if there are entry or extern labels, will be created ".ent" ending and ".ext" ending accordingly. (In case there are errors in a specific file the program will notify the user the errors - to the standart output - and step to the next file.)*/

globals* g;
/*This is an array of structs. The struct is of the actions. The first field is the name of the action, the second field is the opcode of the action, the third field is the amount of operands that this action need to get. (The funct and the opcode will be useful to the second information word in the machine code.)*/
action actArr[ACTION_NUMBER] = {
	{"mov" , 0  , 2},
	{"cmp" , 1  , 2},
	{"add" , 2  , 2},
	{"sub" , 3  , 2},
	{"lea" , 4  , 2},
	{"clr" , 5  , 1},
	{"not" , 6  , 1},
	{"inc" , 7  , 1},
	{"dec" , 8  , 1},
	{"jmp" , 9  , 1},
	{"bne" , 10 , 1},
	{"red" , 11 , 1},
	{"prn" , 12 , 1},
	{"jsr" , 13 , 1},
	{"rts" , 14 , 0},
	{"stop", 15 , 0}
};

/*The main function. Calls to the function that scans the input files.
The variables:
registers: All the possible registers (0 - 15).
f: The current file (with the ".as" ending - the user doesn't type the file with the ending).
f_am: The file that the function sends to "macroSpan" function to print to this file the input after the span.
as_file: the name of the file with ".as" ending.
am_file: the name of the file with ".am" ending.
i: the current file (start from 1 because when argv[0] is the name of the project.
endTrans1: if it is 0, then the input is correct *after the first transition*, else - there are errors. the program notify to the user and step to the next file.
endTrans2: if it is 0, then the input is correct, else - there are errors. the program notify to the user and step to the next file.
endMacro: if it is 1, then the input is correct *after the span*, else - there are errors. the program notify to the user and step to the next file*/
int main(int argc, char* argv[])
{
	char* registers[REGISTER_NUMBER] = {
	  "r0" ,
	  "r1" ,
	  "r2" ,
	  "r3" ,
	  "r4" ,
	  "r5" ,
	  "r6" ,
	  "r7"
	};
	char* asterisk_registers[REGISTER_NUMBER] = {
	  "*r0" ,
	  "*r1" ,
	  "*r2" ,
	  "*r3" ,
	  "*r4" ,
	  "*r5" ,
	  "*r6" ,
	  "*r7"
	};
	FILE* f = NULL;
	FILE* f_am = NULL;
	char* as_file = NULL;
	char* am_file = NULL;
	int i = 1;
	int endMacro;
	int endTrans1;
	int endTrans2;
	if (argc == 1) { /*The user didn't enter files - ERROR*/
		printerrors("", NO_FILE, 0, "");
		return 0;
	}
	while (--argc) {
		/*Initializing the variables*/
		g = (globals*)malloc(sizeof(globals));
		if (g == NULL) {
			printf("Failed to allocate space to list. exiting.\n");
			exit(1);
		}
		memset(g->code, 0, sizeof(g->code));
		memset(g->data, 0, sizeof(g->data));
		g->st_head = NULL;
		g->ent_head = NULL;
		g->ext_head = NULL;
		g->IC = START_IC;
		g->DC = 0;
		g->DCF = 0;
		g->L = 0;
		endMacro = 0;
		endTrans1 = 0;
		endTrans2 = 0;
		g->indexInData = 0;
		g->indexInCodeA = 0;
		g->indexInCodeB = 0;
		as_file = allocationWord(sizeof(argv[i]) + 4);
		am_file = allocationWord(sizeof(argv[i]) + 4);
		strcpy(as_file, argv[i]);
		strcpy(am_file, argv[i]);

		if ((f = fopen(strcat(as_file, ".as"), "r")) == NULL) { /*No file with this name -ERROR*/
			printerrors(argv[i], WORNG_FILE, 0, argv[i]);
			if (argc == 1)
				return 0;
			i++;
			continue;
		}

		f_am = fopen(strcat(am_file, ".am"), "w+");
		if ((endMacro = macroSpan(argv[i], f, f_am)) == FALSE) { /*can't span the file*/
			printerrors("", ERROR_IN_FILE, 1, argv[i]);
			remove(am_file);
			i++;
			continue;
		}
		rewind(f_am);

		if ((endTrans1 = firstTrans(argv[i], f_am, registers, asterisk_registers)) > 0) { /*ERROR in file*/
			printerrors("", ERROR_IN_FILE, endTrans1, argv[i]);
			i++;
			continue;
		}
		fixContentInSymbolTable(); /*finish the symbol tabel*/
		if ((g->IC + g->DC) > MACHINE_CODE_SIZE) { /*the code and data is more than the max size*/
			printerrors(argv[i], NO_MEMMORY, 0, "");
			printerrors("", ERROR_IN_FILE, 1, argv[i]);
			i++;
			continue;
		}
		rewind(f_am);

		if ((endTrans2 = secondTrans(argv[i], f_am, registers, asterisk_registers) > 0))
		{ /*ERROR in file*/
			printerrors("", ERROR_IN_FILE, endTrans2, argv[i]);
			i++;
			continue;
		}
		printfiles(argv[i]); /*O.k, create ".ob", ".ent", ".ext" files.*/
		i++;
	}
        free(as_file);
        free(am_file);
	freeSymbolTabelList();
	freeEntryList();
	freeExternList();
	fclose(f);
	fclose(f_am);
	return 0;
}
