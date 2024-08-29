#ifndef FIRSTPASS_H
#define FIRSTPASS_H
#include <stdio.h>

/**
 * Processes a file line-by-line to handle instructions and validate their correctness.
 *
 * @param fileName The name of the file for error reporting.
 * @param f_am File stream pointer for reading lines.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisks.
 *
 * Reads each line from the file stream, skipping comments and empty lines.
 * Passes valid lines to `first` for processing and counts errors.
 * After processing, checks for `entry` and `extern` labels.
 *
 * @return The total number of errors encountered.
 */
int firstTrans(char* fileName, FILE* f_am, char* registers[], char* asterisk_registers[]);
/**
 * Processes a line of assembly code to handle labels, directives, and instructions.
 *
 * @param fileName The name of the file for error reporting.
 * @param line A line of assembly code to process.
 * @param row The current line number in the file.
 * @param registers An array of register names.
 * @param asterisk_registers An array of register names with an asterisk prefix.
 *
 * This function performs the following:
 * 1. Checks for label syntax and errors.
 * 2. Identifies directives (e.g., ENTRY, EXTERN, DATA, STRING) and processes them accordingly.
 * 3. Handles action instructions and updates the instruction counter.
 * 4. Reports errors if the line contains invalid labels, directives, or commands.
 *
 * @return 0 if the line is processed successfully with no errors,
 *         1 if errors are detected during processing.
 */
int first(char* fileName, char* line, int row, char* registers[], char* asterisk_registers[]);
/**
 * Processes and validates an EXTERN directive in an assembly line.
 *
 * @param fileName The name of the file for error reporting.
 * @param column The current column in the line being processed.
 * @param line The line of assembly code.
 * @param declare Indicates whether it's a declaration (typically used for labels).
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisks.
 * @param row The line number in the file.
 *
 * @return 0 if the EXTERN directive is valid and processed successfully,
 *         1 if there is an error with the EXTERN directive.
 */
int isExtern(char* fileName, int column, char* line, int declare, char* registers[], char* asterisk_registers[], int row);
/**
 * Validates and processes a label line in assembly code, handling labels, directives, and instructions.
 *
 * @param fileName The name of the file for error reporting.
 * @param line The line of assembly code.
 * @param word1 The label or first word in the line.
 * @param row The line number in the file.
 * @param column The column index in the line.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisks.
 *
 * @return 
 *   0 if the label line is processed successfully,
 *   1 if there is an error in the label line,
 *   2 if the label line contains a valid directive but no error.
 */
int checkLabelLine(char* fileName, char* line, char* word1, int row, int column, char* registers[], char* asterisk_registers[]);
/**
 * Adds an entry label to the entry list after validation.
 *
 * @param fileName The file name for error reporting.
 * @param column The starting column of the label in the line.
 * @param line The line of assembly code.
 * @param declare Indicates if the label is being declared.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisks.
 * @param row The line number in the file.
 *
 * @return 
 *   0 if the label is added successfully,
 *   1 if there's an error with the label.
 *
 * The function validates the label, updates the symbol table and entry list,
 * and reports errors if necessary.
 */
int isEntry(char* fileName, int column, char* line, int declare, char* registers[], char* asterisk_registers[], int row);
/**
 * Validates and processes an action line based on its opcode.
 *
 * @param fileName The file name for error reporting.
 * @param trans Indicates the type of translation.
 * @param line The line of assembly code.
 * @param opcode The opcode of the action.
 * @param column The column where the action starts.
 * @param row The line number in the file.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisks.
 *
 * @return 
 *   0 if processing is successful,
 *   1 if there's an error.
 *
 * The function delegates processing to specific functions based on the opcode
 * and updates error status accordingly.
 */
int checkActionLine(char* fileName, int trans, char* line, int opcode, int column, int row, char* registers[], char* asterisk_registers[]);

#endif /* FIRSTPASS_H */













