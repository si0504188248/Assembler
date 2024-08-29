#ifndef MYMACRO_H
#define MYMACRO_H

#include <stdio.h>
#include "MyDataBase.h"
/**
 * Processes a file to handle macro definitions and calls.
 *
 * This function reads a source file line by line, handling macro definitions and calls. It manages
 * macro expansion by storing macro definitions in a linked list and expanding macros when encountered
 * in the source file. The processed output is written to the target file.
 *
 * @param fileName The name of the source file being processed. This is used for error reporting.
 * @param f The input file stream (source file) from which lines are read.
 * @param f_am The output file stream (target file) to which processed lines are written.
 *
 * @return TRUE if the file was processed successfully without critical errors, FALSE otherwise.
 *
 * @note
 * - Handles cases of empty lines, long lines, and various macro-related constructs.
 * - Allocates and deallocates memory for macro lists as needed.
 */
boolean macroSpan(char* fileName, FILE* f, FILE* f_am);
#endif /* MYMACRO_H */

