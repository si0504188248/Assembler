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

boolean method1(char* fileName, char* operand, int row)
{
	int num = 0;
	int i = 1;
	int mask = 0xFFF;
	if (operand[i] == '+' || operand[i] == '-') /*check if the first
	operand is operator*/
		i++;
	if (operand[i] == '\0')
	{ /*ensure that the next char is a digit*/
		printerrors(fileName, ILLEGAL_OPERAND, row, operand);
		return FALSE;
	}
	while (operand[i] != '\0')
	{ /*ensure that all the chars are digits*/
		if (!isdigit(operand[i++]))
		{
			printerrors(fileName, ILLEGAL_OPERAND, row, operand);
			return FALSE;
		}
	}
	num = atoi(operand + 1);
	if (num < MIN_12_BIT_NUM || num > MAX_12_BIT_NUM)
	{
		printerrors(fileName, ILLEGAL_NUMBER, row, "");
		return FALSE;
	}
	else

		if (num < 0)
			num &= mask;
	g->code[g->indexInCodeA] = num;
	g->code[g->indexInCodeA] <<= MOVE_THREE;
	g->code[g->indexInCodeA] |= A; /*encode the number in the correct line*/
	return TRUE;
}


void method3(int j)
{
	g->code[g->indexInCodeA] = MAX_SEVEN_BITS & j;
	g->code[g->indexInCodeA] <<= MOVE_SIX;
	g->code[g->indexInCodeA] |= A;
}

void method3_dest(int j)
{
	int x = 0;
	x |= MAX_SEVEN_BITS & j;
	x <<= MOVE_THREE;
	g->code[g->indexInCodeA] |= x;
	g->code[g->indexInCodeA] |= A;
}


/*This function gets encode the label
the operand.*/
void method4()
{
	g->code[g->indexInCodeA]++;
	g->indexInCodeA++;
	g->L += 1;
}


int operand0(char* fileName, char* actionLine, int column, int trans, int row, int opcode)
{
	if (trans == FIRST_PASS)
		encode_first_word(opcode, EMPTY, EMPTY);
	if (trans == SECOND_PASS)
		g->indexInCodeB++;
	while (actionLine[column++] != '\n')
	{ /*check that the line without
	not-white space chars.*/
		if (!isspace(actionLine[column]))
		{
			printerrors(fileName, MANY_OP, row, "");
			return 1;
		}
	}
	return 0;

}


int operand1(char* fileName, char* actionLine, int column, int trans, int opcode, int row, char* registers[], char* asterisk_registers[])
{
	char* operand;
	char* buf = NULL;
	int j = 0;
	int isOK = 0;
	boolean comma = FALSE;
	column = whiteSpace(actionLine, column); /*go to the next not-white
	space char.*/
	if (actionLine[column] == ',') { /*the first cher is ',' - ERROR.*/
		printerrors(fileName, COMMA, row, "");
		return 1;
	}
	column = whiteSpace(actionLine, column);
	buf = allocationWord(strlen(actionLine));
	strcpy(buf, actionLine);
	while ((j++) < column)
		buf++;
	operand = strtok(buf, " , \t \n \v \f \r");
	column += strlen(operand);
	if (strlen(operand) == 0) { /*there is no operand - ERROR.*/
		printerrors(fileName, NO_OPERAND1, row, "");
		return 1;
	}
	while (actionLine[column] != '\n') { /*check some errors (like
	unnecessary ',')*/
		if (actionLine[column] == ',') {
			comma = TRUE;
			column++;
			if (actionLine[column] == '\n') {
				printerrors(fileName, COMMA, row, actionLine);
				return 1;
			}
		}
		if (!isspace(actionLine[column])) {
			if (comma == TRUE)
				printerrors(fileName, MANY_OP, row, "");
			else
				printerrors(fileName, ILLEGAL_LINE, row, actionLine);
			return 1;
		}
		column++;
	}
	if (comma == TRUE) {
		printerrors(fileName, COMMA, row, actionLine);
		return 1;
	}
	if (trans == FIRST_PASS) {
		isOK = checkOperand(fileName, operand, opcode, row, registers, asterisk_registers); /*check operand*/
	}
	else
		isOK = complet_encoding(fileName, operand, NULL, row, registers, asterisk_registers);

	return isOK;
}


int operand2(char* fileName, char* actionLine, int column, int trans, int opcode, int row, char* registers[], char* asterisk_registers[])
{
	char* operand1;
	char* operand2;
	char buf[MAX_SIZE];
	int isOK = 0;
	boolean comma = FALSE;
	column = whiteSpace(actionLine, column); /*go to the next not-white
	space char.*/
	if (actionLine[column] == ',') { /*the first char is ',' - ERROR.*/
		printerrors(fileName, COMMA, row, "");
		return 1;
	}
	strcpy(buf, actionLine);


	// buf = #1000000000000\0r5\0   \0
	// operand1 = #10000000000
	// operand2 = r5\0
	operand1 = strtok(buf + column, ", \t\n\v\f\r");
	column += strlen(operand1);
	if (strlen(operand1) == 0) { /*there is no operand - ERROR.*/
		printerrors(fileName, NO_OPERAND2, row, "");
		return 1;
	}
	column = whiteSpace(actionLine, column); /*go to the next not-white
	space char.*/
	if (actionLine[column] == '\n') { /*there is no operand - ERROR.*/
		printerrors(fileName, NO_OPERAND2, row, "");
		return 1;
	}
	if (actionLine[column] != ',') { /*the next char is not ',' - ERROR.*/
		printerrors(fileName, NOT_COMMA, row, "");
		return 1;
	}
	column++;
	column = whiteSpace(actionLine, column); /*go to the next not-white
	space char.*/
	if (actionLine[column] == ',') { /*the next char is ',' - ERROR.*/
		printerrors(fileName, COMMA, row, "");
		return 1;
	}

	operand2 = strtok(NULL, ", \t\n\v\f\r");

	column += strlen(operand2);
	while (actionLine[column] != '\n') { /*check some errors (like unnecessary)*/
		if (actionLine[column] == ',') {
			comma = TRUE;
			column++;
			if (actionLine[column] == '\n') {
				printerrors(fileName, COMMA, row, actionLine);
				return 1;
			}

		}
		if (!isspace(actionLine[column])) {
			if (comma == TRUE)
				printerrors(fileName, MANY_OP, row, "");
			else
				printerrors(fileName, ILLEGAL_LINE, row, actionLine);
			return 1;
		}
		column++;
	}
	if (comma == TRUE) {
		printerrors(fileName, COMMA, row, actionLine);
		return 1;
	}
	if (trans == FIRST_PASS)
		isOK = checkOperands(fileName, operand1, operand2, opcode, row, registers, asterisk_registers); /*check operands*/
	else
		isOK = complet_encoding(fileName, operand1, operand2, row, registers, asterisk_registers); /*encode base offset*/
	return isOK;
}


void addRE(int n, int lb_address)
{
	g->code[g->indexInCodeB] = lb_address;
	g->code[g->indexInCodeB] <<= MOVE_THREE;
	g->code[g->indexInCodeB] += n;

}


int complet_encoding(char* fileName, char* operand1, char* operand2, int row, char* registers[], char* asterisk_registers[])
{
	char oplabel[LABEL_SIZE];
	char oplabel1[LABEL_SIZE];
	char* op = operand1;
	char* op1 = operand2;
	int i;
	int isOK = 0;
	int num = 1;
	int lb_address = 0;
	boolean flag = FALSE;
	boolean flagLabel = FALSE;
	symbolTabel* st_node = NULL;
	externList* ext_node = NULL;
	boolean flag1 = FALSE;
	boolean flag2 = FALSE;
	g->indexInCodeB += 1;

	if (operand1 == NULL && operand2 == NULL) {}
	else
	{
		if (operand2 != NULL)
		{
			num = 2;
			strcpy(oplabel, op);
			strcpy(oplabel1, op1);
			for (i = 0; i < REGISTER_NUMBER; i++)
			{
				if (!strcmp(registers[i], op) || !strcmp(asterisk_registers[i], op))
				{
					flag1 = TRUE;
				}
				if (!strcmp(registers[i], op1) || !strcmp(asterisk_registers[i], op1))
				{
					flag2 = TRUE;
				}
			}
		}

		if (flag1 == TRUE && flag2 == TRUE)
			g->indexInCodeB += 1;
		else
		{
			for (i = 0; i < num; i++)
			{

				if (isLabel(fileName, op, 0, row, registers, asterisk_registers) == TRUE) { /*addressing method contains a label*/
					flagLabel = TRUE;
					strcpy(oplabel, op);
				}

				if (flagLabel == TRUE)
				{ /*check if the label is in the symbol tabel, if not - ERROR*/
					st_node = g->st_head;
					while (st_node != NULL)
					{
						if (!strcmp((st_node->symbol), oplabel))
						{
							lb_address = st_node->value;
							flag = TRUE;
							break;
						}
						st_node = st_node->next;
					}
					if (flag == FALSE) {
						printerrors(fileName, LABEL_NOT_FOUND, row, oplabel);
						return 1;
					}
					if (!strcmp((st_node->attributes), "external")) { /*label is extern label*/
						ext_node = allocationExternList(ext_node); /*put the label in extern list*/
						g->ext_head = addContentToExternNode(ext_node, st_node->symbol, g->indexInCodeB + START_IC);

						addRE(E, lb_address); /*encode the label*/

					}
					else /*label is not extern label*/
					{

						addRE(R, lb_address); /*encode the label*/

					}


				}
				flagLabel = FALSE;
				memset(oplabel, '\0', LABEL_SIZE);
				if (operand2 != NULL)
					strcpy(op, operand2);
				g->indexInCodeB += 1;
			}
		}
	}
	return isOK;

}


int checkOperand(char* fileName, char* operand, int opcode, int row, char* registers[], char* asterisk_registers[])
{
	int j;
	boolean flag = TRUE;
	int error = 0;
	if (operand[0] == '#')
	{
		if (opcode != PRN)
		{
			printerrors(fileName, ILLEGAL_TARGET, row, operand);
			return 1;
		}

		encode_first_word(opcode, EMPTY, IMM_METHOD);
		if (method1(fileName, operand, row) == FALSE)
			return 1;
		flag = FALSE;
		g->indexInCodeA++;
		g->L++;
	}

	for (j = 0; j < REGISTER_NUMBER; j++)
	{
		if (flag == TRUE && !strcmp(operand, registers[j]))
		{
			if (opcode == JMP || opcode == BNE || opcode == JSR)
			{
				printerrors(fileName, ILLEGAL_TARGET, row, operand);
				return 1;
			}
			encode_first_word(opcode, EMPTY, REG_METHOD);
			method3_dest(j);
			g->indexInCodeA++;
			g->L++;
			flag = FALSE;
		}
		if (flag == TRUE && !strcmp(operand, asterisk_registers[j]))
		{

			encode_first_word(opcode, EMPTY, REG_ASTRIKE_METHOD);
			method3_dest(j);
			g->indexInCodeA++;
			g->L++;
			flag = FALSE;
		}
	}

	if (flag == TRUE && isLabel(fileName, operand, 0, row, registers, asterisk_registers) == TRUE)
	{

		encode_first_word(opcode, EMPTY, DIRECT_METHOD);
		method4();
		flag = FALSE;
	}
	j = 0;
	if (flag == TRUE) {
		printerrors(fileName, ILLEGAL_OPERAND, row, operand);
		return 1;
	}


	return error;
}



int checkOperands(char* fileName, char* operand1, char* operand2, int
	opcode, int row, char* registers[], char* asterisk_registers[])
{
	boolean flag = TRUE;
	boolean go = FALSE;
	boolean directly = FALSE;
	boolean reg = FALSE;
	int error = 0;
	int j;
	int src_operand = EMPTY;
	int dst_operand = EMPTY;
	int index = g->indexInCodeA;
	int index1;
	int x = 0;
	g->indexInCodeA++;
	g->L = 0;

	if (operand1[0] == '#')
	{
		if (opcode == LEA) { /*addressing method not for "lea" action (in
		actions that get 2 operands)*/
			printerrors(fileName, ILLEGAL_SOURCE, row, operand1);
			return 1;
		}
		src_operand = IMM_METHOD;
		directly = TRUE; /*first addressing method*/
		flag = FALSE;
	}
	for (j = 0; j < REGISTER_NUMBER; j++)
	{
		if ((flag == TRUE && (!strcmp(operand1, registers[j]))) || (flag == TRUE &&
			!strcmp(operand1, asterisk_registers[j])))
		{
			if (!strcmp(operand1, asterisk_registers[j]))
				src_operand = REG_ASTRIKE_METHOD;
			else
				src_operand = REG_METHOD;
			if (opcode == LEA)
			{
				/*addressing method not for "lea" action (in actions that get 2 operands)*/
				printerrors(fileName, ILLEGAL_SOURCE, row, operand1);
				return 1;
			}
			method3(j);
			flag = FALSE;
			reg = TRUE; /*register addressing method*/
		}
	}

	if (flag == TRUE && isLabel(fileName, operand1, 0, row, registers, asterisk_registers) == TRUE) {
		method4();
		src_operand = DIRECT_METHOD;
		flag = FALSE;
		go = TRUE; /*addressing method contains label*/
	}
	if (flag == TRUE) {
		printerrors(fileName, ILLEGAL_OPERAND, row, operand2);
		return 1;
	}
	flag = TRUE;
	for (j = 0; j < REGISTER_NUMBER; j++) {
		if (flag == TRUE && (!strcmp(operand2, registers[j]) ||
			!strcmp(operand2, asterisk_registers[j])))
		{
			if (!strcmp(operand2, asterisk_registers[j]))
				dst_operand = REG_ASTRIKE_METHOD;
			else
				dst_operand = REG_METHOD;
			if (directly == TRUE) { /*first operand is first addressing method*/
				if (method1(fileName, operand1, row) == FALSE) /*incorrect
				addressing method*/
					return 1;
				g->L += 1;
				g->indexInCodeA++;
				directly = FALSE;
			}
			method3_dest(j);
			flag = FALSE;
			g->L += 1;
			g->indexInCodeA++;
		}
	}
	if (flag == TRUE && operand2[0] == '#')
	{
		dst_operand = IMM_METHOD;
		if (opcode != CMP) { /*addressing method just for "cmp" action
		(in the actions that get 2 operands)*/
			printerrors(fileName, ILLEGAL_TARGET, row, operand2);
			return 1;
		}
		if (reg == TRUE) { /*first operand is registers addressing method*/
			g->indexInCodeA++;
			g->L++;
			reg = FALSE;
		}
		if (directly == TRUE) { /*first operand is first addressing method*/
			if (method1(fileName, operand1, row) == FALSE) /*incorrect
			addressing method*/
				return 1;
			directly = FALSE;
			g->indexInCodeA++;
			g->L++;
		}
		if (method1(fileName, operand2, row) == FALSE) /*incorrect
		addressing method*/
			return 1;
		flag = FALSE;
		g->indexInCodeA++;
		g->L += 1;
	}
	if (flag == TRUE && isLabel(fileName, operand2, 0, row, registers, asterisk_registers) == TRUE)
	{

		dst_operand = DIRECT_METHOD;
		flag = FALSE;
		if (directly == TRUE) { /*first operand is first addressing method*/
			if (method1(fileName, operand1, row) == FALSE) /*incorrect
			addressing method*/
				return 1;
			directly = FALSE;
			g->indexInCodeA += 1;
			g->L += 1;
		}
		if (go == TRUE) { /*first operand is addressing method contains label*/
			go = FALSE;
		}
		else {
			g->indexInCodeA += 1;
			g->L += 1;
		}
		method4();
	}
	if (flag == TRUE) {
		printerrors(fileName, ILLEGAL_OPERAND, row, operand2);
		return 1;
	}
	x = g->indexInCodeA;
	g->indexInCodeA = index;
	index1 = x;
	encode_first_word(opcode, src_operand, dst_operand);
	g->indexInCodeA = index1;
	return error;
}



void  encode_first_word(int opcode, int src_operand, int dest_operand)
{
	int bit_src_index = src_operand + TURN_SRC_BIT;
	int bit_dest_index = dest_operand + TURN_DST_BIT;
	unsigned short word = 0;
	unsigned short binary_representation;
	unsigned int mask1;
	unsigned int mask2;
	/*1. Store the number in only 4 bits */
	binary_representation = opcode & OP_CODE;
	/* 2. Initialize code word to zero */
	/* 3. Place the number in positions 11-14 */
	word |= (binary_representation << MOVE_ELEVEN);
	/*Creating the mask to light the chip*/
	mask1 = 1 << bit_src_index;
	mask2 = 1 << bit_dest_index;
	/*the desired fiber ignition*/
	if (src_operand != EMPTY)
		word |= mask1;
	if (dest_operand != EMPTY)
		word |= mask2;
	word |= A;
	g->code[g->indexInCodeA] = word;
	g->indexInCodeA++;
	g->L++;

}

