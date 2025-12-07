#ifndef PENQUIN_PARSER_H
#define PENQUIN_PARSER_H

#include <stdbool.h>
#include "common.h"
#include "list.h"
#include "token.h"

typedef struct {
	char *path;
	List tokens;
	List nodes;
} File;

typedef struct {
	bool pointer;
	String type;
	String name;
} Parameter;

typedef struct {
	bool pointer;
	String name;
} Type;

typedef struct {
	List parameters;
	List statements;
	Type *type;
} Function;

typedef struct {
	List statements;
} Block;

typedef enum {
    AST_NUMBER,
    AST_STRING,
    AST_VARIABLE,
    AST_FUNCTION,
    AST_WHILE,
    AST_IF,
    AST_BLOCK,

    AST_OPERATOR,
    AST_ASSIGNMENT,
    AST_FUNCTION_CALL,
	
    AST_IMPORT,
    AST_ACCESSOR,

    AST_FILE,
} AstType;


typedef struct AstNode {
    AstType type;
    union {
        float number;
        enum TokenType op;
        String string;
		List arguments;
		Block block;
		Function fn;
		File file;
		struct AstNode *condition;
    } as;
    struct AstNode *left;
    struct AstNode *right;
} AstNode;


void parse(List *t, List *nodes);
AstNode *parse_file(char *path, List *t);

#endif
