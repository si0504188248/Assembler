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

/*allocations functions*/
entryList* allocationEntryList(entryList* ent_node)
{
	ent_node = (entryList*)malloc(sizeof(entryList));
	if (ent_node == NULL) {
		printf("Failed to allocate space to list. exiting.\n");
		exit(1);
	}
	return ent_node;
}

externList* allocationExternList(externList* ext_node)
{
	ext_node = (externList*)malloc(sizeof(externList));
	if (ext_node == NULL) {
		printf("Failed to allocate space to list. exiting.\n");
		exit(1);
	}
	return ext_node;
}


symbolTabel* allocationSymbolTabelList(symbolTabel* node)
{
	node = (symbolTabel*)malloc(sizeof(symbolTabel));
	if (node == NULL) {
		printf("Failed to allocate space to list. exiting.\n");
		exit(1);
	}
	return node;
}

macroList* allocationMacroList()
{
	macroList* node = (macroList*)malloc(sizeof(macroList));
	if (node == NULL) {
		printf("Failed to allocate space to list. exiting.\n");
		exit(1);
	}
	return node;
}

/*add content functions*/
symbolTabel* addContentToSymbolTabelNode(symbolTabel* node, char* symbol, int value, char* attributes)
{
	strtok(symbol, ":");
	strcpy((node->symbol), symbol);
	node->value = value;
	strcpy((node->attributes), attributes);
	node->next = g->st_head;
	return node;
}

externList* addContentToExternNode(externList* ext, char label[], int add)
{
	strcpy(ext->label, label);
	ext->address = add;
	ext->next = g->ext_head;
	return ext;
}

entryList* addContentToEntryNode(entryList* node, char* word, int row)
{
	strcpy(node->label, word);
	node->row = row;
	node->next = g->ent_head;
	return node;
}


/*free list functions*/
void freeSymbolTabelList()
{
	symbolTabel* node;
	while (g->st_head != NULL) {
		node = g->st_head;
		g->st_head = g->st_head->next;
		free(node);
	}
}

void freeMacroList(macroList* head)
{
	macroList* node;
	while (head != NULL) {
		node = head;
		head = head->next;
		free(node);
	}
}

void freeEntryList()
{
	entryList* node;
	while (g->ent_head != NULL) {
		node = g->ent_head;
		g->ent_head = g->ent_head->next;
		free(node);
	}
}

void freeExternList()
{
	externList* node;
	while (g->ext_head != NULL) {
		node = g->ext_head;
		g->ext_head = g->ext_head->next;
		free(node);
	}
}

/*reverse list functions*/
symbolTabel* reverseSymbolTabelList()
{
	symbolTabel* node = NULL;
	while (g->st_head != NULL) {
		symbolTabel* newNode = g->st_head;
		g->st_head = g->st_head->next;
		newNode->next = node;
		node = newNode;
	}
	return node;
}

entryList* reverseEntryList() {
	entryList* node = NULL;
	while (g->ent_head != NULL) {
		entryList* newNode = g->ent_head;
		g->ent_head = g->ent_head->next;
		newNode->next = node;
		node = newNode;
	}
	return node;
}

externList* reverseExternList()
{
	externList* node = NULL;
	while (g->ext_head != NULL) {
		externList* newNode = g->ext_head;
		g->ext_head = g->ext_head->next;
		newNode->next = node;
		node = newNode;
	}
	return node;
}


void fixContentInSymbolTable()
{
	int oldValue = 0, ICF = g->IC;
	symbolTabel* node;
	g->st_head = reverseSymbolTabelList(); /*the list is reverse*/
	node = g->st_head;
	while (node != NULL) {
		if (!strcmp(node->attributes, "data")) {
			oldValue = node->value;
			node->value = ICF;
			ICF += oldValue;
		}
		node = node->next;
	}

}


int checkEntryExtern(char* fileName, int row)
{
	symbolTabel* node;
	node = g->st_head;
	while (node != NULL) {
		if (!strcmp(node->attributes, "external") && !strcmp(node->attributes2, "entry")) {
			printerrors(fileName, ENTRY_EXTERN, row, node->symbol);
			return 1;
		}
		node = node->next;
	}
	return 0;
}
