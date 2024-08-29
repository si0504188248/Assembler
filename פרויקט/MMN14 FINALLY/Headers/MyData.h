#ifndef MYDATA_H
#define MYDATA_H
/**
 * Processes a line of data and validates its format.
 *
 * This function checks a line of data to ensure it conforms to the expected format for data lines. It validates characters,
 * processes numbers with optional signs, and handles comma separators. It also updates the data array with valid numbers.
 *
 * @param fileName The name of the source file for error reporting.
 * @param dataLine The line of data to be processed.
 * @param row The line number in the source file for error reporting.
 * @param column The starting column in the line to begin processing.
 *
 * @return Returns the number of valid data items processed if successful; otherwise, returns -2 for errors.
 */
int isData(char* fileName, char dataLine[], int row, int column);


/**
 * Processes and validates a string line, extracting its content and encoding it into data.
 *
 * This function checks if a line represents a valid string, starting and ending with double quotes. It extracts the content
 * of the string, ensures all characters are printable, and encodes each character into a data array.
 *
 * @param fileName The name of the source file for error reporting.
 * @param stringLine The line of text to be processed as a string.
 * @param row The line number in the source file for error reporting.
 * @param column The starting column in the line to begin processing.
 *
 * @return Returns the length of the string (excluding quotes) if successful; otherwise, returns -2 for errors.
 */
int isString(char* fileName, char stringLine[], int row, int column);
#endif /* MYDATA_H */
