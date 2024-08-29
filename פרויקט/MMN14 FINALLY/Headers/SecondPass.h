#ifndef SECONDPASS_H
#define SECONDPASS_H

#include <stdio.h>
/**
 * Processes the second pass of an assembler for a given file.
 *
 * This function performs the second pass of an assembler, where it verifies labels 
 * declared as `.entry` are correctly defined, and processes each line of the file to
 * handle the final assembly steps.
 *
 * @param fileName The name of the file being processed.
 * @param f_am The file pointer for the assembly file where the second pass is performed.
 * @param registers An array of register names used in the assembler.
 * @param asterisk_registers An array of special register names with an asterisk used in the assembler.
 * 
 * @return Returns the number of errors encountered during the second pass.
 *         Returns `0` if no errors were encountered.
 *
 * The function performs the following steps:
 * 1. Verifies that all labels declared with `.entry` are defined.
 * 2. Processes each line of the assembly file:
 *    - Skips comment lines (lines starting with `;`).
 *    - Skips empty lines.
 *    - Sends non-empty, non-comment lines to the `second` function for further processing.
 * 3. Increments and tracks the row number while processing lines.
 * 4. Returns the total count of errors found during processing.
 */
int secondTrans(char* fileName, FILE* f_am, char* registers[], char* asterisk_registers[]);

/**
 * Processes a single line of assembly code during the second pass of assembly.
 *
 * This function handles the processing of a line of assembly code, including checking
 * for labels, verifying actions, and performing any necessary updates or error checking.
 *
 * @param fileName The name of the file being processed.
 * @param line The line of assembly code to be processed.
 * @param row The current row number in the file.
 * @param registers An array of register names used in the assembler.
 * @param asterisk_registers An array of special register names with an asterisk used in the assembler.
 *
 * @return Returns the number of errors found in the line of code.
 *         Returns `0` if no errors were found in the line.
 *
 * The function performs the following steps:
 * 1. Trims leading whitespace from the line and extracts the first and second words.
 * 2. Checks if the first word is a label and if it is defined in the symbol table.
 *    - If it is a label, updates the entry list with the label's information.
 * 3. Checks if the first or second word is a valid action and verifies the action line.
 * 4. Returns the total count of errors found during processing of the line.
 */
int second(char* fileName, char* line, int row, char* registers[], char* asterisk_registers[]);
#endif /* SECONDPASS_H */
