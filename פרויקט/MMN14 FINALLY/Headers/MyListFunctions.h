#ifndef MYLISTFUNCTIONS_H
#define MYLISTFUNCTIONS_H

#include "MyDataBase.h"

/**
 * Allocates memory for a new entryList node.
 *
 * This function allocates memory for a new node of type entryList. If the allocation fails,
 * it prints an error message and terminates the program.
 *
 * @param ent_node A pointer to an entryList node. This parameter is used for passing in the pointer to the allocated node.
 *
 * @return A pointer to the newly allocated entryList node.
 *
 * @note If memory allocation fails, the program will terminate.
 */
entryList* allocationEntryList(entryList* ent_node);
/**
 * Allocates memory for a new externList node.
 *
 * This function allocates memory for a new node of type externList. If the allocation fails,
 * it prints an error message and terminates the program.
 *
 * @param ext_node A pointer to an externList node. This parameter is used for passing in the pointer to the allocated node.
 *
 * @return A pointer to the newly allocated externList node.
 *
 * @note If memory allocation fails, the program will terminate.
 */

externList* allocationExternList(externList* ext_node);
/**
 * Allocates memory for a new symbolTabel node.
 *
 * This function allocates memory for a new node of type symbolTabel. If the allocation fails,
 * it prints an error message and terminates the program.
 *
 * @param node A pointer to a symbolTabel node. This parameter is used for passing in the pointer to the allocated node.
 *
 * @return A pointer to the newly allocated symbolTabel node.
 *
 * @note If memory allocation fails, the program will terminate.
 */

symbolTabel* allocationSymbolTabelList(symbolTabel* node);
/**
 * Allocates memory for a new macro list node.
 *
 * This function allocates memory for a new `macroList` node. If memory allocation fails,
 * the program will print an error message and exit.
 *
 * @param node A pointer to a `macroList` node. This parameter will be updated to point
 *             to the newly allocated node. If `node` is NULL, a new memory block is allocated
 *             and assigned to this pointer.
 *
 * @return A pointer to the newly allocated `macroList` node.
 *
 * @note If memory allocation fails, the function will terminate the program.
 */
macroList* allocationMacroList();
/**
 * Adds content to a symbol table node and updates the list.
 *
 * This function sets the symbol, value, and attributes for a given symbol table node and
 * updates the node to point to the current head of the symbol table list. It then returns
 * the updated node.
 *
 * @param node A pointer to a symbolTabel node to be updated.
 * @param symbol A string containing the symbol to be added to the node. The function removes
 *               the trailing colon (':') if present.
 * @param value An integer representing the value associated with the symbol.
 * @param attributes A string representing the attributes of the symbol (e.g., "external", "internal").
 *
 * @return A pointer to the updated symbolTabel node with the new symbol, value, and attributes,
 *         and an updated next pointer.
 *
 * @note The function assumes that the symbolTabel node has been previously allocated and is valid.
 */

symbolTabel* addContentToSymbolTabelNode(symbolTabel* node, char* symbol, int value, char* attributes);
/**
 * Adds content to a new external list node and updates the list.
 *
 * This function sets the `label` of the provided `externList` node to the given label,
 * and inserts this node at the beginning of the external list. The `next` pointer of the
 * new node is set to the current head of the external list, and then the head is updated
 * to point to this new node.
 *
 * @param ext A pointer to the `externList` node to be updated. This node's `label` will
 *            be set to the provided `label`, and its `next` pointer will be updated to
 *            point to the current head of the external list.
 * @param label A string containing the label to be added to the node.
 *
 * @return A pointer to the updated `externList` node, now at the head of the list.
 *
 * @note The function does not allocate memory for the `externList` node. It is assumed
 *       that the node has already been allocated before calling this function.
 */

externList* addContentToExternNode(externList* ext, char label[], int add);
/**
 * Adds content to a new entry list node and updates the list.
 *
 * This function sets the `label` of the provided `entryList` node to the given `word`,
 * and sets the `row` of the node to the provided `row`. The node's `next` pointer is
 * updated to point to the current head of the entry list, and then the head is updated
 * to point to this new node.
 *
 * @param node A pointer to the `entryList` node to be updated. This node's `label` will
 *             be set to the provided `word`, and its `row` will be set to the provided `row`.
 *             The `next` pointer of the node will be updated to point to the current head
 *             of the entry list.
 * @param word A string containing the label to be added to the node.
 * @param row An integer representing the row number associated with this entry.
 *
 * @return A pointer to the updated `entryList` node, now at the head of the list.
 *
 * @note The function does not allocate memory for the `entryList` node. It is assumed
 *       that the node has already been allocated before calling this function.
 */

entryList* addContentToEntryNode(entryList* node, char* word, int row);

/**
 * Frees the memory allocated for the symbol table list.
 *
 * This function iterates through the entire symbol table list, starting from the
 * head node, and frees the memory allocated for each node in the list. After the
 * memory for all nodes has been freed, the head pointer of the symbol table list
 * is set to `NULL`.
 */

void freeSymbolTabelList();
/**
 * Frees the memory allocated for the macro list.
 *
 * This function iterates through the entire macro list, starting from the head node,
 * and frees the memory allocated for each node in the list. After the memory for all
 * nodes has been freed, the head pointer is set to `NULL`.
 *
 * @param head A pointer to the head node of the macro list.
 */
void freeMacroList(macroList* head);
/**
 * Frees the memory allocated for the entry list.
 *
 * This function iterates through the entire entry list, starting from the head node,
 * and frees the memory allocated for each node in the list. After the memory for all
 * nodes has been freed, the head pointer of the entry list is set to `NULL`.
 */
void freeEntryList();
/**
 * Frees all nodes in the extern list.
 *
 * This function iterates through the entire extern list, freeing each node in turn.
 * It sets the head of the extern list to `NULL` once all nodes have been freed.
 */

void freeExternList();
/**
 * Reverses the order of the nodes in the symbol table list.
 *
 * This function takes the current symbol table list and reverses the order of its nodes.
 * It iterates through the entire list, updating the `next` pointers of each node to point
 * to the previous node, effectively reversing the list.
 *
 * @return symbolTabel* The new head of the reversed symbol table list.
 */

symbolTabel* reverseSymbolTabelList();
/**
 * Reverses the order of the entry list.
 *
 * This function iterates through the entire entry list and reverses the order of the nodes.
 * It returns a pointer to the new head of the reversed list.
 *
 * @return A pointer to the new head of the reversed entry list.
 */
entryList* reverseEntryList();
/**
 * Reverses the external list.
 *
 * This function reverses the order of the nodes in the external list, which is used to keep track
 * of external labels. It iterates through the list and reverses the link directions between nodes,
 * resulting in a new list with the nodes in reverse order.
 *
 * @return A pointer to the head of the reversed external list.
 */
externList* reverseExternList();

/**
 * Fixes the content in the symbol table based on the current instruction count (ICF).
 *
 * This function adjusts the values in the symbol table for entries marked as "data".
 * It first reverses the symbol table list to process entries in the correct order,
 * then updates the values for data entries by setting them to the current instruction count (ICF)
 * and adjusts the ICF based on the previous value of each entry.
 *
 * The function does not return any value.
 */
void fixContentInSymbolTable();

/**
 * Checks for errors in the entry and external attributes of symbols.
 *
 * This function verifies whether any symbol in the symbol table is marked as both "external" and
 * "entry". Such a condition is invalid and should be flagged as an error. The function prints an
 * appropriate error message if such a symbol is found.
 *
 * @param fileName The name of the source file being processed. This is used for error reporting.
 * @param row The row number in the source file where the error was detected. This is used for error reporting.
 *
 * @return 1 if an error is found (symbol marked as both "external" and "entry"), 0 otherwise.
 */
int checkEntryExtern(char* fileName, int row);
#endif /* MYLISTFUNCTIONS_H */



