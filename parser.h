#ifndef PENQUIN_PARSER_H
#define PENQUIN_PARSER_H

#include <stdbool.h>
#include "common.h"
#include "list.h"

typedef struct {
	bool pointer;
	String type;
	String name;
} Parameter;

typedef enum {
    AST_NUMBER,
    AST_STRING,
    AST_VARIABLE,
    AST_FUNCTION,

    AST_OPERATOR,
    AST_ASSIGNMENT,
    AST_FUNCTION_CALL,
} AstType;


typedef struct AstNode {
    AstType type;
    union {
        float number;
        char operator;
        String string;
		List arguments;
		List parameters;
    } as;
    struct AstNode *left;
    struct AstNode *right;
} AstNode;


void parse(List *t, List *nodes);

#endif
