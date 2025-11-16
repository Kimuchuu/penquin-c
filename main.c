#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "parser.h"
#include "codegen.h"

void read_file(FILE *file, char **data) {
    fseek(file, 0, SEEK_END);
    fpos_t pos;
    fgetpos(file, &pos);
    int size = pos.__pos;

    *data = malloc((size + 1) * sizeof(char));

    rewind(file);
    fread(*data, sizeof(char), size, file);
    (*data)[size] = '\0';
}

int main(int argc, char **argv) {
    printf("STDC_VERSION: %ld\n", __STDC_VERSION__);

    char *buffer;
    read_file(stdin, &buffer);
    printf("\nfile size: %ld\n", strlen(buffer));
    List tokens = {0};
    list_init(&tokens, sizeof(Token));
    scan(buffer, &tokens);

    printf("nubmer of tokens: %d\n", tokens.length);
    for (int i = 0; i < tokens.length; i++) {
        Token t = ((Token *)tokens.elements)[i];
        printf("token %s\n", token_type_to_string(t.type));
    }

    List nodes = {0};
    list_init(&nodes, sizeof(AstNode *));

    parse(&tokens, &nodes);
    compile(&nodes);

    return 0;
}
