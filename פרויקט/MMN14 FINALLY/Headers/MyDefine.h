#ifndef MYDEFINE_H
#define MYDEFINE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define A 4 /*the value of A in the first part*/
#define R 2 /*the value of R in the first part*/
#define E 1 /*the value of E in the first part*/
#define EMPTY -1/**/
#define FIRST_PASS 1/**/
#define SECOND_PASS 2/**/
#define MOV 0/**/
#define CMP 1/**/
#define LEA 4/**/
#define CLR 5/**/
#define JMP 9/**/
#define BNE 10/**/
#define PRN 12/**/
#define JSR 13/**/
#define RTS 14/**/
#define STOP 15/**/
#define IMM_METHOD 0/**/
#define DIRECT_METHOD 1/**/
#define REG_ASTRIKE_METHOD 2/**/
#define REG_METHOD 3/**/
#define ENTRY_SIZE 6/**/
#define DATA_SIZE 5/**/
#define CODE_SIZE 5/**/

/*ERRORS - When the program finds an error - then it prints to the standart output the file of the error, the line of the error and a little description and step to the next line. (of-corse, in this case won't create the output files)*/
#define WARNING_LABEL 400 /*if there is a label before .entry or .extern directive.*/
#define EMPTY_FILE 401 /*if the current file is an empty file.*/
#define ILLEGAL_SOURCE 402 /*if source operand illegal to this opcode.*/
#define ERROR_IN_FILE 403 /*all the errors in a specific file.*/
#define COMMA 404 /*if there is a comma not in the place (like one after the other and more).*/
#define NOT_COMMA 405 /*if there are 2 operands without comma bitween them.*/
#define MANY_OP 406 /*if there are too many operands for one action.*/
#define LABEL_NOT_FOUND 407 /*if there is a label that not in the symboltabel.*/
#define ILLEGAL_REGIST 408 /*if there is an illegal register in the index.*/
#define ILLEGAL_LINE 409 /*if there is a line that the first word is not legal word.*/
#define NO_FILE 410 /*if there are no filesin the command line.*/
#define WORNG_FILE 411 /*if the name of the file is worng.*/
#define ILLEGAL_OPERAND 412 /*if the operand is worng.*/
#define ILLEGAL_DATA 413 /*if the data line is worng.*/
#define ILLEGAL_STRING 414 /*if the string line is worng.*/
#define ILLEGAL_LABEL 415 /*if the name of the label is illegal (like 1MAIN).*/
#define LABEL_TWICE 416 /*if there is a label that already defined.*/
#define NO_MEMMORY 417 /*if there is no enough memmory.*/
#define NO_OPERAND2 418 /*if there is just one operand (instead of 2).*/
#define NO_OPERAND1 419 /*if there is no operand (instead of 1).*/
#define LONG_LINE 420 /*if there is too long line.*/
#define ENTRY_EXTERN 421 /*if there is label that defined as both entry and extern.*/
#define EXTERN_DEFINE 422 /*if there is label that declared as extern and also as regular.*/
#define JUST_ENTRY 423 /*if there is label declared as entry, and in practice didn't declared.*/
#define ILLEGAL_COMMAND 425 /*an unknown command (foreach first word in line without ":" in end or "." in the begining)*/
#define LABEL_SPACE 426 /*after label must be a space.*/
#define WARNING_EXTERN 427 /*if an extern label defined twice.*/
#define WARNING_ENTRY 428 /*if an entry label defined twice.*/
#define FIRST_LETTER 431 /*first char of a label isn't a letter.*/
#define ALPHANUMERIC_LABEL 432 /*chars in a label are not letters or numbers.*/
#define RESERVED_WORD 433 /*label is a reserved word.*/
#define LONG_LABEL 434 /*label is too long.*/
#define ILLEGAL_NUMBER 435 /*number isn't in the range (MIN_NUM-MAX_NUM).*/
#define ILLEGAL_TARGET 436 /*if target operand illegal to this opcode.*/
#define INDEX_OPERAND 437 /*if target operand illegal to this opcode.*/
#define ILLEGAL_DIRECTIVE 438 /*if target operand illegal to this opcode.*/
#define LABEL_EMPTY_LINE 439

#endif /* MYDEFINE_H */
