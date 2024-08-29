#ifndef MYCODE_H
#define MYCODE_H
#include "MyDataBase.h"
/**
 * Analyzes and encodes an operand for direct addressing.
 *
 * @param fileName The name of the source file for error reporting.
 * @param operand The operand to analyze.
 * @param row The current line number in the file.
 *
 * @return 
 *   TRUE if the operand is valid and encoded successfully,
 *   FALSE if there is an error in the operand.
 *
 * The function checks if the operand is a valid number within the 12-bit range,
 * and encodes it in a specified format. Errors are reported if the operand is invalid.
 */
boolean method1(char* fileName, char* operand, int row);

/**
 * Encodes a register number into a code format.
 *
 * @param j The register number to encode.
 *
 * This function takes a register number and encodes it into a specific format
 * by performing bitwise operations. The result is stored in the global code array
 * at the current index.
 */
void method3(int j);

/**
 * Encodes a register number into a code format.
 *
 * @param j The register number to encode.
 *
 * This function takes a register number and encodes it into a specific format
 * by performing bitwise operations. The result is stored in the global code array
 * at the current index.
 */
void method3_dest(int j);

/**
 * Updates the global code array and index for encoding.
 *
 * This function increments the value at the current index of the global code array,
 * advances the index, and updates the length of the current line.
 */
void method4();

/**
 * Increments the current value in the global code array, advances the index, and updates the length.
 *
 * This function performs the following actions:
 * 1. Increments the value at the current index in the global code array (`g->code[g->indexInCodeA]`).
 * 2. Advances the index in the global code array (`g->indexInCodeA`).
 * 3. Updates the length of the current line (`g->L`).
 */
int operand0(char* fileName, char* actionLine, int column, int trans, int row, int opcode);

/**
 * Processes and validates the first operand of an instruction in the given action line.
 *
 * @param fileName The name of the current file (used for error reporting).
 * @param actionLine The line of code being analyzed.
 * @param column The starting column for the operand.
 * @param trans A flag indicating the type of operand processing (1 for checking operand, other values for completion encoding).
 * @param opcode The operation code related to the operand.
 * @param row The current line number (used for error reporting).
 * @param registers Array of register names (used for operand validation).
 * @param asterisk_registers Array of special register names (used for operand validation).
 * @return 0 if the operand is valid and processed successfully, 1 if an error occurs.
 *
 * The function performs the following:
 * 1. Skips white spaces and validates that the operand starts correctly.
 * 2. Extracts and verifies the operand from the action line.
 * 3. Checks for syntax errors such as misplaced commas or additional operands.
 * 4. Calls the appropriate functions to validate and encode the operand based on the `trans` flag.
 */
int operand1(char* fileName, char* actionLine, int column, int trans,int opcode, int row, char* registers[], char* asterisk_registers[]);

/**
 * Processes and validates two operands in an action line.
 *
 * This function performs the following:
 * 1. Skips whitespace and checks for errors related to operand formatting and placement.
 * 2. Extracts two operands from the action line.
 * 3. Validates the operands and handles errors related to their presence or formatting.
 * 4. Depending on the `trans` flag, either validates the operands or completes their encoding.
 *
 * @param fileName Name of the file for error reporting.
 * @param actionLine The line of code containing the operands.
 * @param column Starting position of the first operand in `actionLine`.
 * @param trans Processing type flag indicating how to handle the operands.
 * @param opcode Operation code related to the operands.
 * @param row Line number in the file for error reporting.
 * @param registers Array of register names used for validation.
 * @param asterisk_registers Array of special register names used for validation.
 *
 * @return 0 if processing is successful, 1 if an error is encountered.
 */
int operand2(char* fileName, char* actionLine, int column, int trans, int opcode, int row, char* registers[], char* asterisk_registers[]);

/**
 * Updates the code array with a new entry and increments the index.
 *
 * This function performs the following:
 * 1. Adds the `lb_address` to the current position in the code array.
 * 2. Shifts the address left by 3 bits.
 * 3. Adds `n` to the least significant bits of the address.
 * 4. Increments the index for the next entry.
 *
 * @param n Value to be added to the code entry.
 * @param lb_address Address to be encoded in the code array.
 */
void addRE(int n, int lb_address);

/**
 * Completes encoding of operands and updates code and external lists.
 *
 * This function performs the following:
 * 1. Advances the code index by 2.
 * 2. Processes each operand:
 *    - For immediate values (starting with '#'), increments the code index.
 *    - If the operand is a label, it looks up the label in the symbol table.
 *    - If the label is found and is external, it is added to the external list and encoded.
 *    - If the label is not external, it is encoded directly.
 *    - If the label is not found, an error is reported.
 *
 * @param fileName The name of the source file for error reporting.
 * @param operand1 The first operand to be encoded.
 * @param operand2 The second operand to be encoded (optional).
 * @param row The line number in the source file for error reporting.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisk notation.
 *
 * @return Returns 0 if encoding is successful, otherwise returns 1 for errors.
 */
int complet_encoding(char* fileName, char* operand1, char* operand2, int row, char* registers[], char* asterisk_registers[]);

/**
 * Checks and encodes an operand based on its type and opcode.
 *
 * This function performs the following:
 * 1. If the operand is an immediate value (starts with '#'), checks if the opcode is valid for immediate values, encodes it, and updates the code index and length.
 * 2. If the operand matches a register name, it checks if the opcode is valid for register operands, encodes it, and updates the code index and length.
 * 3. If the operand matches an asterisk register, it encodes it with a specific addressing method.
 * 4. If the operand is a label, it encodes it using label-specific methods.
 * 5. If the operand is invalid, reports an error.
 *
 * @param fileName The name of the source file for error reporting.
 * @param operand The operand to be checked and encoded.
 * @param opcode The operation code to determine the valid operand types.
 * @param row The line number in the source file for error reporting.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisk notation.
 *
 * @return Returns 0 if the operand is valid and encoding is successful; otherwise, returns 1 for errors.
 */

int checkOperand(char* fileName, char* operand, int opcode, int row, char* registers[], char* asterisk_registers[]);

/**
 * Checks and encodes two operands based on their types and the opcode.
 *
 * This function processes two operands for an assembly instruction and encodes them according to their addressing methods.
 * It performs the following steps:
 * 1. Checks if the first operand is an immediate value, a register, or a label, and encodes it accordingly.
 * 2. Checks if the second operand is an immediate value, a register, or a label, and encodes it accordingly.
 * 3. Handles errors related to incorrect operand types or formats.
 * 4. Updates the code index and length based on the encoded operands.
 *
 * @param fileName The name of the source file for error reporting.
 * @param operand1 The first operand to be checked and encoded.
 * @param operand2 The second operand to be checked and encoded.
 * @param opcode The operation code to determine the valid operand types.
 * @param row The line number in the source file for error reporting.
 * @param registers Array of register names.
 * @param asterisk_registers Array of register names with asterisk notation.
 *
 * @return Returns 0 if the operands are valid and encoding is successful; otherwise, returns 1 for errors.
 */
int checkOperands(char* fileName, char* operand1, char* operand2, int opcode, int row, char* registers[], char* asterisk_registers[]);

/**
	 * Encodes the first word of an instruction based on the opcode, source operand, and destination operand.
	 *
	 * @param opcode The operation code to be encoded (4-bit representation).
	 * @param src_operand The source operand index (bit position for source operand).
	 * @param dest_operand The destination operand index (bit position for destination operand).
	 *
	 * The function performs the following:
	 * 1. Initializes the encoding word to zero.
	 * 2. Encodes the opcode into the most significant 4 bits (positions 14-11).
	 * 3. Sets the bit for the source operand if it is valid (not -1).
	 * 4. Sets the bit for the destination operand if it is valid (not -1).
	 * 5. Always sets bit 2 of the encoding word.
	 * 6. Stores the result in the global code array at the current index and updates the index and length.
	 */
void  encode_first_word(int opcode, int src_operand, int dest_operand);


#endif /* MYCODE_H */


