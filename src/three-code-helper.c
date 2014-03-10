#include "three-code-helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>	// INT32_MAX/MIN
#include <float.h>	// for FLT_MAX, FLT_MIN
#include <math.h>	// for NAN

static uint32_t __place;

uint32_t genPlace()
{
	uint32_t copy = __place;
	++__place;
	
	return copy;
}

uint32_t getPlace() { return __place; }

void resetPlace()
{
	__place = 0;
}

uint32_t genLabel()
{
	static uint32_t counter; // static data is initialized to 0 by default
	
	uint32_t copy = counter;
	++counter;
	
	return copy;
}

void InstrNode_print(const InstructionNode *node)
{
	assert(node && "node is null");
	
	switch(node->instrType)
	{
	case INSTR_ADD:	
		printf("\tadd_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_SUB:
		printf("\tsub_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_MUL:
		printf("\tmul_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_DIV:
		printf("\tdiv_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_REM:
		printf("\trem_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_RET: // return from function
		if( strcmp(node->type, "void") == 0 ) // if the return doesn't return anything
			printf("\tret\n");
		else
			printf("\tret_%s from %%%u\n", node->type, node->inPlace0);
		break;
		
	case INSTR_ASSIGN:
		printf("\tassign to %%%u from %%%u\n", node->destPlace, node->inPlace0);
		break;
		
	case INSTR_LOAD_FROM_OFFSET:
		printf("\tload to %%%u from %%%u(%%%u)\n", node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_LOAD_INT:
		printf("\tload_int %%%u %s\n", node->destPlace, node->value);
		break;
	
	case INSTR_LOAD_FLOAT:
		printf("\tload_float %%%u %s\n", node->destPlace, node->value);
		break;
		
	case INSTR_FUNC_CALL:
		printf("\tcall %s into %%%u\n", node->value, node->destPlace);
		break;
		
	case INSTR_FUNC_PARAM_PUSH:
		printf("\tpush_param %%%u\n", node->inPlace0);
		break;
		
	case INSTR_FUNC_PARAMS_POP:
		printf("\tpop_params %s\n", node->value);
		break;
		
	case INSTR_FUNC_LABEL:
		printf("\n%s:\n", node->value);
		break;
		
	case INSTR_LESS:
		printf("\tless_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
	
	case INSTR_LESS_EQUAL:
		printf("\tless_equal_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_EQUAL:
		printf("\tequal_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_NOT_EQUAL:
		printf("\tnot_equal_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_GREATER:
		printf("\tgreater_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_GREATER_EQUAL:
		printf("\tgreater_equal_%s to %%%u from %%%u %%%u\n", node->type, node->destPlace, node->inPlace0, node->inPlace1);
		break;
		
	case INSTR_IF_NOT:
		printf("\tif_not %%%u goto .L%u\n", node->inPlace0, node->after);
		break;
		
	case INSTR_WHILE_NOT:
		printf("\tWHILE_not %%%u goto .L%u\n", node->inPlace0, node->after);
		break;
		
	case INSTR_LABEL:
		printf(".L%u:\n", node->after);
		break;
	
	case INSTR_1ST_ARG_PLACE:
		printf("@%u\n", node->inPlace0);
		break;
		
	case INSTR_WRITELN:
		printf("\t__writeln_%s %%%u\n", node->type, node->inPlace0);
		break;
		
	case INSTR_READ_INT:
		printf("\t__readInt to %%%u\n", node->destPlace);
		break;
		
	case INSTR_UNCONDITIONAL_JUMP:
		printf("\tjump .L%u\n", node->begin);
		break;
	
	default:
		assert(0 && "node->instrType is not handled or has an invalid value");
	}
}

/// allocates and returns a new instruction list
InstructionList* InstrList_create()
{
	InstructionList *list = (InstructionList*)malloc(sizeof(InstructionList));
	assert(list && "memory allocation failed");
	
	list->head = NULL;
	list->length = 0;
}

/// de-allocates all nodes in the list and the list itself
void InstrList_destroy(InstructionList *list)
{
	assert(list && "list is null");
	
	InstructionNode *p, *prev;
	
	p = list->head;
	while( p )
	{
		prev = p;
		p = p->next;
		free(prev);
	}
	
	free(list);
}

/// inserts a new node into an instruction list
void InstrList_insert(InstructionList *list, InstructionNode *node)
{
	assert(list && "list is null");
	assert(node && "node is null");
	
	assert(node->next == NULL && "node->next must be null but it's not. Maybe you forgot to set it to null?");
	
	if( list->head == NULL )
	{
		list->head = node;
	}
	else
	{
		InstructionNode *p, *prev;
		p = prev = list->head;
		while( p != NULL )
		{
			prev = p;
			p = p->next;
		}
		prev->next = node;
	}
	
	++list->length;
}

void InstrList_print(const InstructionList *list)
{
	assert(list && "list is null");
	
	InstructionNode *n = list->head;
	
	while( n != NULL )
	{
		InstrNode_print(n);
		n = n->next;
	}
}

/// return how many instructions of type "instrType" exist
uint32_t InstrList_count(const InstructionList *list, InstructionType instrType)
{
	assert(list && "list is null");

	uint32_t count = 0;
	
	InstructionNode *n = list->head;
	while( n != NULL )
	{
		if( n->instrType == instrType )
			++count;
		
		n = n->next;
	}
	
	return count;
}

/// ----------------------------------------------------------------------------------------

/// returns a string that will represent the name of the given function in the generated code
const char* genStringForFunc(char *result, const Symbol *symbol)
{
	assert(result && "result buffer is null");
	assert(symbol && "symbol is null");

	if( strcmp(symbol->name, "main") == 0 )
		sprintf(result, "%s", symbol->name);
	else
	{
		sprintf(result, "_%s", symbol->name);
	
		unsigned short i;
		for(i = 0; i < symbol->numParams; ++i)
			sprintf(result + strlen(result), "_%s", symbol->params[i]);
	}
	
	return result;
}

/// returns the number of args in a function, e.g _foo_int_int will return 2
/// it is used with getStringForFunc()
uint32_t getNumOfArguments(const char *funcStr)
{
	assert(funcStr && "funcStr is null");
	uint32_t len = strlen(funcStr);
	
	int index = len - 1; // go to the last character
	int count = 0;
	
	while( index >= 0 )
	{
		if( funcStr[index] == '_' )
			++count;
			
		--index;
	}
	
	if( count <= 1 )
		return 0;
	
	return count - 1;
}

void codeGenAdd(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_ADD;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

void codeGenSub(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_SUB;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// generates code for a multiplication
void codeGenMul(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_MUL;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// generates code for a division
void codeGenDiv(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_DIV;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// generates code for a remainder
void codeGenRem(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_REM;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// generates code for a return statement
void codeGenReturn(InstructionList *list, const char *type, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_RET;
	n->inPlace0 = inPlace;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// assigns a value from inPlace to destPlace
void codeGenAssign(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_ASSIGN;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

void codeGenLoadFromOffset(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace, uint32_t offsetPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_LOAD_FROM_OFFSET;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace;
	n->inPlace1 = offsetPlace;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// concatenates src into dest
void InstrList_concat(InstructionList *dest, const InstructionList *src)
{
	assert(dest && "dest is null");
	assert(src && "src is null");
	
	InstructionNode *n = src->head;
	while( n != NULL )
	{
		InstructionNode *temp = (InstructionNode*)malloc(sizeof(InstructionNode));
		memcpy(temp, n, sizeof(InstructionNode));
		temp->next = NULL;
		InstrList_insert(dest, temp);
		
		n = n->next;
	}
}

/// stores val(int) into destPlace
void codeGenLoadInt(InstructionList *list, uint32_t destPlace, int val)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_LOAD_INT;
	n->destPlace = destPlace;
	sprintf(n->value, "%d", val);
	
	InstrList_insert(list, n);
}

/// stores val(float into destPlace
void codeGenLoadFloat(InstructionList *list, uint32_t destPlace, float val)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_LOAD_FLOAT;
	n->destPlace = destPlace;
	sprintf(n->value, "%f", val);
	
	InstrList_insert(list, n);
}


/// function call
void codeGenFuncCall(InstructionList *list, const Symbol *func, uint32_t destPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	char buffer[1000];
	
	n->next = NULL;
	n->instrType = INSTR_FUNC_CALL;
	n->destPlace = destPlace;
	strcpy(n->value, genStringForFunc(buffer, func));
	strcpy(n->type, func->type);
	
	InstrList_insert(list, n);
}

/// generates code to push a function parameter
void codeGenPushParam(InstructionList *list, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_FUNC_PARAM_PUSH;
	n->inPlace0 = inPlace;
	
	InstrList_insert(list, n);
}

void codeGenPopParams(InstructionList *list, uint32_t numParams)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_FUNC_PARAMS_POP;
	sprintf(n->value, "%u", numParams);
	
	InstrList_insert(list, n);
}

/// generates code for a fuction label
void codeGenFuncLabel(InstructionList *list, const Symbol *func)
{
	assert(func && "func is null");
	
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	char buffer[1000];
	
	n->next = NULL;
	n->instrType = INSTR_FUNC_LABEL;
	strcpy(n->value, genStringForFunc(buffer, func));
	
	InstrList_insert(list, n);
}

/// generates code for comparison operators (<, <=, ==, >=, >)
void codeGenComparisonOp(InstructionList *list, const char *type, InstructionType instrType, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1)
{
	assert((instrType == INSTR_LESS || instrType == INSTR_LESS_EQUAL || instrType == INSTR_EQUAL || instrType == INSTR_NOT_EQUAL ||
			instrType == INSTR_GREATER || instrType == INSTR_GREATER_EQUAL) && "instrType must be <, <=, ==, !=, >= or >");
			
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = instrType;
	n->destPlace = destPlace;
	n->inPlace0 = inPlace0;
	n->inPlace1 = inPlace1;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

void codeGenIfNot(InstructionList *list, uint32_t destLabel, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_IF_NOT;
	n->after = destLabel;
	n->inPlace0 = inPlace;
	
	InstrList_insert(list, n);
}

/// generates code for a "while not" statement
void codeGenWhileNot(InstructionList *list, uint32_t startLabel, uint32_t destLabel, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_WHILE_NOT;
	n->begin = startLabel;
	n->after = destLabel;
	n->inPlace0 = inPlace;
	
	InstrList_insert(list, n);
}

/// generates a label that an "if" statement can jump to
void codeGenLabel(InstructionList *list, uint32_t label)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_LABEL;
	n->after = label;
	
	InstrList_insert(list, n);
}

/// generates code for a property
void codeGenProperty(InstructionList *list, const char *type, const char *property, uint32_t destPlace, int32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	char buffer[1000];
	
	n->next = NULL;
	n->destPlace = destPlace;
	strcpy(n->type, type);
	
	if( strcmp(type, "int") == 0 )
	{
		if(	strcmp(property, "max") == 0 )			sprintf(buffer, "%d", INT32_MAX);
		else if( strcmp(property, "min") == 0 )		sprintf(buffer, "%d", INT32_MIN);
		else if( strcmp(property, "sizeof") == 0 )	sprintf(buffer, "%d", 4);
		else if( strcmp(property, "init") == 0 )	sprintf(buffer, "%d", 0);
		
		n->instrType = INSTR_LOAD_INT;
	}
	else if( strcmp(type, "float") == 0 )
	{
		if(	strcmp(property, "max") == 0 )			{ sprintf(buffer, "%f", FLT_MAX); n->instrType = INSTR_LOAD_FLOAT; }
		else if( strcmp(property, "min") == 0 )		{ sprintf(buffer, "%f", FLT_MIN); n->instrType = INSTR_LOAD_FLOAT; }
		else if( strcmp(property, "sizeof") == 0 )	{ sprintf(buffer, "%d", 4); n->instrType = INSTR_LOAD_INT; }
		else if( strcmp(property, "init") == 0 )	{ sprintf(buffer, "%f", NAN); n->instrType = INSTR_LOAD_FLOAT; }
	}
	else if( strcmp(type, "int[]") == 0 )
	{
		if(	strcmp(property, "length") == 0 )
		{
			n->instrType = INSTR_LOAD_FROM_OFFSET;
			n->inPlace0 = inPlace;
			n->inPlace1 = 1;
			strcpy(n->type, type);
		}
		//fprintf(stderr, "warning: .length property is not implemented.\n");
	}
	else if( strcmp(type, "float[]") == 0 )
	{
		if(	strcmp(property, "length") == 0 )
			fprintf(stderr, "warning: .length property is not implemented.\n");
	}
	
	strcpy(n->value, buffer);
	
	InstrList_insert(list, n);
}

void codeGenFirstArgPlace(InstructionList *list)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_1ST_ARG_PLACE;
	n->inPlace0 = getPlace();
	
	InstrList_insert(list, n);
}

/// generates code to writeln
void codeGenWriteln(InstructionList *list, const char *type, uint32_t inPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_WRITELN;
	n->inPlace0 = inPlace;
	strcpy(n->type, type);
	
	InstrList_insert(list, n);
}

/// reads an integer from stdin and returns it to destPlace
void codeGenReadInt(InstructionList *list, uint32_t destPlace)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_READ_INT;
	n->destPlace = destPlace;
	
	InstrList_insert(list, n);
}

void codeGenUnconditionalJump(InstructionList *list, uint32_t label)
{
	InstructionNode *n = (InstructionNode*)malloc(sizeof(InstructionNode));
	assert(n && "memory allocation for instructionNode failed");
	
	n->next = NULL;
	n->instrType = INSTR_UNCONDITIONAL_JUMP;
	n->begin = label;
	
	InstrList_insert(list, n);
}
