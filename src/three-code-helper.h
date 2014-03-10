#ifndef __THREE_CODE_HELPER_H__
#define __THREE_CODE_HELPER_H__

#include <stdint.h>

#include "symbol.h"

typedef enum
{
	/* 0 */ INSTR_ADD,
	/* 1 */ INSTR_SUB,
	/* 2 */ INSTR_MUL,
	/* 3 */ INSTR_DIV,
	/* 4 */ INSTR_REM,						// remainder (%)
	/* 5 */ INSTR_RET,						// return statement
	/* 6 */ INSTR_ASSIGN,					// assigment operator (could be mv on some platforms)
	/* 7 */ INSTR_LOAD_INT,					// load an immediate int
	/* 8 */ INSTR_LOAD_FLOAT,				// load an immediate float
	/* 9 */ INSTR_FUNC_CALL,				// function call
	/* 10 */ INSTR_FUNC_PARAM_PUSH,			// pushes an argument for a function into the stack
	/* 11 */ INSTR_FUNC_PARAMS_POP,			// pops the arguments what were pushed for the function call
	/* 12 */ INSTR_FUNC_LABEL,				// the function's label
	/* 13 */ INSTR_LESS,					// <
	/* 14 */ INSTR_LESS_EQUAL,				// <=
	/* 15 */ INSTR_EQUAL,					// ==
	/* 16 */ INSTR_NOT_EQUAL,				// !=
	/* 17 */ INSTR_GREATER,					// >
	/* 18 */ INSTR_GREATER_EQUAL,			// >=
	/* 19 */ INSTR_IF_NOT,					// if! (if not)
	/* 20 */ INSTR_WHILE_NOT,				// while not
	/* 21 */ INSTR_LABEL,					// an if's statement label
	/* 22 */ INSTR_PROPERTY,				// type properties
	/* 23 */ INSTR_1ST_ARG_PLACE,			// pseudo command that prints the place the 1st argument in a function (so the function
											// can know where is its 1st argument stored. If it knows that, it can learn where the other args are too
	/* 24 */ INSTR_WRITELN,					// writes something into the screen and print a newline after
	/* 25 */ INSTR_UNCONDITIONAL_JUMP,		// unconditional jump
	/* 26 */ INSTR_LOAD_FROM_OFFSET,		// load a value from an offset
	/* 27 */ INSTR_READ_INT
	
} InstructionType;

/// returns an unsigned integer that is used for temporary locations. on each successive call, a bigger number is returned.
/// the counter is reset when resetPlace() is called
uint32_t genPlace();

/// returns the last generated place
uint32_t getPlace();

/// resets the place counter
void resetPlace();

/// returns a unique unsigned integer that will be used as an assembly label
uint32_t genLabel();

typedef struct _InstructionNode
{
	InstructionType instrType;
	
	uint32_t begin, after; // begin/after labels. used by "if", "while" etc
	
	uint32_t destPlace;	// destination register
	uint32_t inPlace0;
	uint32_t inPlace1;	// 2nd input register (may not apply to all instructions)
	
	char type[100];		// type of the operands
	char value[100];	// value (e.g 0, 10, -1, 0.0f). Used for loadImmediate, function names
	
	char userData[1000];	// the user can put anything here
	
	struct _InstructionNode *next;
	
} InstructionNode;

void InstrNode_print(const InstructionNode *node);

/// -------------------------------------------------------------------

typedef struct _InstructionList
{
	InstructionNode *head;
	uint32_t length;
	
} InstructionList;


/// allocates and returns a new instruction list
InstructionList* InstrList_create();

/// de-allocates all nodes in the list and the list itself
void InstrList_destroy(InstructionList *list);

/// inserts a new node into an instruction list
void InstrList_insert(InstructionList *list, InstructionNode *node);

/// prints a list to stdout
void InstrList_print(const InstructionList *list);

/// concatenates src into dest
void InstrList_concat(InstructionList *dest, const InstructionList *src);

/// return how many instructions of type "instrType" exist
uint32_t InstrList_count(const InstructionList *list, InstructionType instrType);

/// ---------------------------------------------------------------------------------------------------------------------------------

/// returns a string that will represent the name of the given function in the generated code
/// @param result buffer where the string will be written
/// @return the contents of "result" are returned
const char* genStringForFunc(char *result, const Symbol *symbol);

/// returns the number of args in a function, e.g _foo_int_int will return 2
/// it is used with getStringForFunc()
uint32_t getNumOfArguments(const char *funcStr);

/// generates code for an addition
void codeGenAdd(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for a subtraction
void codeGenSub(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for a multiplication
void codeGenMul(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for a division
void codeGenDiv(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for a remainder
void codeGenRem(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for a return statement
void codeGenReturn(InstructionList *list, const char *type, uint32_t inPlace);

/// assigns a value from inPlace to destPlace (operator = )
void codeGenAssign(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace);

/// loads a value to destplace from inPlace + offsetPlace
void codeGenLoadFromOffset(InstructionList *list, const char *type, uint32_t destPlace, uint32_t inPlace, uint32_t offsetPlace);

/// stores val(int) into destPlace
void codeGenLoadInt(InstructionList *list, uint32_t destPlace, int val);

/// stores val(float into destPlace
void codeGenLoadFloat(InstructionList *list, uint32_t destPlace, float val);

/// function call
/// @param destPlace the register to store the function's return value into
void codeGenFuncCall(InstructionList *list, const Symbol *func, uint32_t destPlace);

/// generates code to push a function parameter
void codeGenPushParam(InstructionList *list, uint32_t inPlace);

/// generates code to pop all parameters that were pushed later for a function call
/// @param numParams the number of parameters to pop. The actual number of bytes is not our concern
void codeGenPopParams(InstructionList *list, uint32_t numParams);

/// generates code for a fuction label
void codeGenFuncLabel(InstructionList *list, const Symbol *func);

/// generates code for comparison operators (<, <=, ==, >=, >)
void codeGenComparisonOp(InstructionList *list, const char *type, InstructionType instrType, uint32_t destPlace, uint32_t inPlace0, uint32_t inPlace1);

/// generates code for an "if not" statement
/// @param destLabel label to just to if the "if not" won't execute
/// @param inPlace the register to read from
void codeGenIfNot(InstructionList *list, uint32_t destLabel, uint32_t inPlace);

/// generates code for a "while not" statement
void codeGenWhileNot(InstructionList *list, uint32_t startLabel, uint32_t destLabel, uint32_t inPlace);

/// generates a label that an "if" statement can jump to
void codeGenLabel(InstructionList *list, uint32_t label);

/// generates code for a property
/// @symbol Needed for arrays to read the .length value
void codeGenProperty(InstructionList *list, const char *type, const char *property, uint32_t destPlace, int32_t inPlace);

/// 
void codeGenFirstArgPlace(InstructionList *list);

/// generates code to writeln
void codeGenWriteln(InstructionList *list, const char *type, uint32_t inPlace);

/// reads an integer from stdin and returns it to destPlace
void codeGenReadInt(InstructionList *list, uint32_t destPlace);

/// unconditionally jump to label "label"
void codeGenUnconditionalJump(InstructionList *list, uint32_t label);

#endif
