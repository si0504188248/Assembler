#ifndef MYDATABASE_H
#define MYDATABASE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SIZE 83 /*maximum length of line*/
#define MAX_12_BIT_NUM 4096 /*maximun number for 12 bits*/
#define MIN_12_BIT_NUM -4096 /*nimimum number for 12 bits*/
#define MAX_15_BIT_NUM 32767/*maximun number for 15 bits*/
#define MIN_15_BIT_NUM -32767 /*nimimum number for 15 bits*/
#define LABEL_SIZE 34 /*maximum length of label*/
#define MACRO_SIZE 10 /*maximum lines in a macro*/
#define FILE_SIZE 260 /*maximum length of file name*/
#define MACHINE_CODE_SIZE 4096 /*the size of the RAM*/
#define REGISTER_NUMBER 8 /*amount of the registers*/
#define ACTION_NUMBER 16 /*amount of the actions*/
#define START_IC 100 /*the first address of the machine code*/
#define MASK 0xFFF /*for specific bits*/
#define MOVE_THREE 3 /*for move three bits*/
#define MOVE_SIX 6 /*for move six bits*/
#define MAX_SEVEN_BITS 7 /*encoding for maximum 3 bits*/
#define MOVE_ELEVEN 11 /*for move eleven bits*/
#define TURN_SRC_BIT 7 
#define TURN_DST_BIT 3 
#define OP_CODE 0xF /*for encode the opcode*/

typedef enum { FALSE, TRUE } boolean;
typedef enum { DATA, STRING, ENTRY, EXTERN, NONE } directiveType;


/*A struct for the actions. This struct contains the name fo the function, the opcode, the funct, and the amount of the operands this action can get. This is an arry of structs that initialized in the main file (it is a global array)*/
typedef struct {
	char name[5];
	int opcode;
	int operand_num;
}action;

/*An entry list - for the entry labels. This list contains the label, the base, the offset, the row that the label defined, and the "next" - pointer to the next node.*/
typedef struct entryList {
	char label[LABEL_SIZE];
	int row;
	struct entryList* next;
}entryList;

/*An extern list - for the extern labels. This list contains the label, the base, the offset, and the "next" - pointer to the next node.*/
typedef struct externList {
	char label[LABEL_SIZE];
        int address;
	struct externList* next;
}externList;

/*A macro list - for the macros. This list contains the number of the lines in the macro, the name, the lines in the macro, and the "next" - pointer to the next node.*/
typedef struct macroList {
	int numOfLines;
	char name[LABEL_SIZE];
	char macroLines[MACRO_SIZE][MAX_SIZE];
	struct macroList* next;
}macroList;

/*A symbol tabel list - for the labels. This list contains the label, the value(address), the base, the offset, the attributes, another attributes to "entry", and the "next" - pointer to the next node.*/
typedef struct symbolTabel {
	char symbol[LABEL_SIZE];
	int value;

	char attributes[9];
	char attributes2[9];
	struct symbolTabel* next;
}symbolTabel;


/*This is a struct for all the globals variabels. the struct contains:
1. The counters.
2. The arrays of the data and the code. In this array I will preforming the binary encoding and according this binary encoding, the ".ob" file will be created.
3. The head of the three lists in the program.*/
typedef struct globals {
	int IC;  /*counts the code (and all the information word).*/
	int DC;  /*counts the data.*/
	int DCF; /*counts the data value of the lines without labels.*/
	int L;   /*counts for each action the amount of information word to the current action.*/
	int indexInCodeA; /*signifies the current place in the code array in the first transition.*/
	int indexInData;  /*signifies the current place in the code array in the second transition.*/
	int indexInCodeB; /*signifies the current place in the data array in.*/
	int code[MACHINE_CODE_SIZE];
	int data[MACHINE_CODE_SIZE];
	entryList* ent_head;  /*head for entryList - the labels that defined as entry, with base and offset.*/
	externList* ext_head; /*head for externList - the labels that defined as entry, with base and offset.*/
	symbolTabel* st_head; /*head for symbolTabel - the labels with addres, base, offset, and attributes.*/
}globals;


extern globals* g;
extern action actArr[ACTION_NUMBER];
#endif /* MYDATABASE_H */
