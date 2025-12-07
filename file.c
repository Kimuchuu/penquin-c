#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

char *get_directory(char *path) {
	char *dirc = cstring_duplicate(path);
	char *dname = dirname(dirc);
	return dname;
}

char *path_to_name(char *path) {
	int path_length = strlen(path);
	int begin_name_index = -1;
	for (int i = 0; i < path_length; i++) {
		if (path[i] == '/') {
			begin_name_index = i;
		}
	}
	begin_name_index++;
	
	int name_length = path_length - begin_name_index - 3;
	char *name = malloc(sizeof(char) * (name_length + 1));
	memcpy(name, path + begin_name_index, name_length);
	name[name_length] = '\0';
	return name;
}

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

void read_file_from_path(char *path, char **data) {
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		perror("Unable open file");
	}
	read_file(file, data);
	fclose(file);
}
