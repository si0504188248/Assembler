#ifndef MYPRINT_H
#define MYPRINT_H



/**
 * Generates output files from the assembled code.
 *
 * This function creates three output files based on the assembled code: 
 * - An object file (.ob) containing the code and data sections.
 * - An entry file (.ent) listing entry labels and their addresses.
 * - An extern file (.ext) listing external labels.
 *
 * The output files are created in the current directory with the base name specified by `file`.
 * 
 * @param file The base name for the output files (without extensions). The following files will be created:
 *             - `<file>.ob` for the object file.
 *             - `<file>.ent` for the entry file.
 *             - `<file>.ext` for the extern file.
 * 
 * @return Returns 0 upon successful creation of the files.
 * 
 * @note
 * - Allocates memory for file names and ensures proper file handling.
 * - The object file contains the code and data sections with their respective addresses.
 * - The entry file lists symbols marked as "entry" with their addresses.
 * - The extern file lists symbols marked as "extern".
 */
int printfiles(char* file);

/**
 * Prints error or warning messages based on the specified error code.
 *
 * This function is used to report various types of errors or warnings encountered during
 * the processing of assembly code files. The function prints the message to the standard output.
 *
 * @param fileName The name of the file where the error or warning occurred.
 * @param flag The error or warning code indicating the type of issue. See below for possible values.
 * @param row The line number in the file where the issue was found.
 * @param word The problematic word or label, if applicable. May be `NULL` if not relevant.
 * 
 * @return Returns `0` after printing the message.
 * 
 * Error and warning codes (`flag` values):
 * - NO_FILE: No files found. Exit the program.
 * - ILLEGAL_COMMAND: Illegal command name in the specified file.
 * - ILLEGAL_DIRECTIVE: Illegal directive name in the specified file.
 * - EMPTY_FILE: The specified file is empty.
 * - LABEL_SPACE: Expected space after label in the specified file.
 * - WARNING_EXTERN: Label already declared as `.extern`; ignoring the statement.
 * - WARNING_ENTRY: Label already declared as `.entry`; ignoring the statement.
 * - COMMA: Comma not in the correct place in the specified file.
 * - MANY_OP: Too many arguments in the specified file.
 * - ILLEGAL_LINE: Illegal line content in the specified file.
 * - WORNG_FILE: Cannot find the specified file; proceeding to the next file.
 * - ILLEGAL_DATA: Illegal data line in the specified file.
 * - ILLEGAL_STRING: Illegal string line in the specified file.
 * - NUMBER_REGIST: Register must be a number between 10 and 15.
 * - MUST_REGIST: Expected register between `[]` in the specified file.
 * - FIRST_LETTER: The first character in a label must be a letter.
 * - ALPHANUMERIC_LABEL: A label must contain only alphanumeric characters.
 * - ILLEGAL_LABEL: Illegal label name in the specified file.
 * - RESERVED_WORD: Label name is a reserved word; illegal.
 * - LONG_LABEL: Label name exceeds 32 characters.
 * - NO_MEMMORY: Out of memory for the specified file; proceeding to the next file.
 * - ILLEGAL_NUMBER: Number is out of the acceptable range in the specified file.
 * - INDEX_OPERAND: Expected `[` in index addressing method.
 * - NO_OPERAND2: Expected 2 arguments in the specified file.
 * - NO_OPERAND1: Expected 1 argument in the specified file.
 * - LABEL_NOT_FOUND: Label not found in the specified file.
 * - ILLEGAL_OPERAND: Illegal operand in the specified file.
 * - NOT_COMMA: Missing comma between arguments in the specified file.
 * - LABEL_TWICE: Label already declared in the specified file.
 * - LONG_LINE: Line exceeds 80 characters in the specified file.
 * - ERROR_IN_FILE: Errors in the file; cannot create `.ob` file.
 * - EXTERN_DEFINE: Label already defined as an extern label.
 * - ENTRY_EXTERN: Label defined as both `.entry` and `.extern`.
 * - ILLEGAL_SOURCE: Illegal source operand; not yet defined.
 * - ILLEGAL_TARGET: Target operand is illegal for the command.
 * - WARNING_LABEL: Label before `.entry` or `.extern` directive; ignoring the label.
 * - JUST_ENTRY: Label declared as `.entry` but not defined.
 * - ILLEGAL_REGIST: Illegal register name in the specified file.
 */
int printerrors(char* fileName, int flag, int row, char* word);
#endif /* MYPRINT_H */

