#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include "MyDataBase.h"
/**
 * Skips whitespace characters in a line of text and returns the index of the first non-whitespace character.
 *
 * This function advances the index `i` while it encounters whitespace characters (such as spaces, tabs) in the provided
 * `line`. The function stops advancing when it reaches a non-whitespace character or the end of the line (newline character).
 *
 * @param line The line of text to be processed.
 * @param i The current index in the line to start skipping whitespace characters.
 *
 * @return The index of the first non-whitespace character, or the index at the end of the line if all characters are whitespace.
 */
int whiteSpace(char* line, int i);
/**
 * Extracts the next word from a string starting at a given column.
 *
 * This function finds and copies the next word from the input string, beginning at the specified column.
 *
 * @param line The input string to scan.
 * @param column The starting index in the string.
 * @param word Buffer to copy the extracted word into. Must be large enough to hold the word and the null terminator.
 *
 * @return The length of the extracted word, or `0` if no word is found.
 */
int nextWord(char* line, int column, char* word);

/**
 * Checks if the length of a line exceeds the maximum allowed length.
 *
 * This function determines if the length of the given `line` exceeds a predefined maximum length, which is specified
 * by the constant `MAX_SIZE`. The function counts the number of characters in the line up to the newline character and
 * checks if it exceeds the maximum allowed length. If the line's length exceeds `MAX_SIZE - 3`, it returns `TRUE`;
 * otherwise, it returns `FALSE`.
 *
 * @param line The line of text to be checked.
 *
 * @return `TRUE` if the line's length exceeds `MAX_SIZE - 3`, otherwise `FALSE`.
 */
boolean longLine(char* line);

/**
 * Retrieves the opcode for a given action name.
 *
 * This function searches for the `word` in an array of action names and returns the corresponding opcode if found.
 * If the `word` does not match any action names in the array, it returns `-1`.
 *
 * @param word The action name to search for in the array.
 *
 * @return The opcode associated with the action name if found, otherwise `-1`.
 */
int actions(char* word);

/**
 * Determines the type of directive based on the provided word.
 *
 * This function checks if the `word` matches one of the predefined directive keywords and returns the corresponding
 * directive type. If the word does not match any known directives, it returns `UNKNOWN_DIRECTIVE`.
 *
 * @param word The directive keyword to be checked.
 *
 * @return The type of directive corresponding to the provided keyword:
 *         - `DATA` for ".data"
 *         - `STRING` for ".string"
 *         - `ENTRY` for ".entry"
 *         - `EXTERN` for ".extern"
 *         - `UNKNOWN_DIRECTIVE` if the keyword does not match any known directives.
 */
directiveType directive(char* word);

/**
 * Checks if the given line is empty or contains only whitespace characters.
 *
 * This function examines the `line` to determine if it consists solely of whitespace characters or if it is entirely empty.
 * It returns `TRUE` if the line is empty or contains only whitespace characters, and `FALSE` otherwise.
 *
 * @param line The line of text to be checked.
 *
 * @return `TRUE` if the line is empty or contains only whitespace characters; `FALSE` otherwise.
 */
boolean emptyLine(char* line);

/**
 * Checks if a given word is a valid label according to specific rules.
 *
 * This function validates if the provided `word` is a valid label based on the following rules:
 * - The label must start with an alphabetic character.
 * - The label must not exceed the maximum allowed length.
 * - The label must not be a reserved keyword or directive.
 * - The label must not match any of the predefined register names.
 * - The label must only contain alphanumeric characters (letters and digits).
 * If the label is being declared (indicated by `declare`), it must end with a colon (':').
 *
 * @param fileName The name of the file where the label is used (for error reporting).
 * @param word The label to be checked.
 * @param declare Indicates if the label is being declared (non-zero) or used (zero).
 * @param row The line number in the file where the label is located (for error reporting).
 * @param registers An array of valid register names.
 * @param asterisk_registers An array of valid register names with asterisks.
 *
 * @return `1` if the label is valid, otherwise returns `0` or an appropriate error code.
 */
int isLabel(char* fileName, char* word, int declare, int row, char* registers[], char* asterisk_registers[]);
/**
 * Allocates memory for a character array with the specified size.
 *
 * This function allocates memory for a character array of the given size. If the allocation fails,
 * it prints an error message and terminates the program.
 *
 * @param size The number of bytes to allocate.
 *
 * @return A pointer to the allocated character array.
 *
 * @note If memory allocation fails, the program will terminate.
 */
char* allocationWord(int size);
#endif /* MYFUNCTIONS_H */
