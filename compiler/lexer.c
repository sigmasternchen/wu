#include "compiler.h"

#include <stdbool.h>

size_t line_no = 0;
size_t line_pos = 0;

static size_t input_offset = 0;
static char* input_text = NULL;
static char* current_token = NULL;

void lexer_init(FILE* input_file) {
	lexer_cleanup();
	input_offset = 0;
	line_no = 0;
	line_pos = 0;

	fseek(input_file, 0, SEEK_END);
	long file_size = ftell(input_file);
	rewind(input_file);

	input_text = malloc(file_size + 1);
	if (input_text == NULL) {
		panic("lexer_init");
	}

	fread(input_text, file_size, 1, input_file);

	input_text[file_size] = 0;
}

static bool is_delimiter(char c) {
	return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

char* next_token() {
	free(current_token);
	current_token = malloc(256);
	size_t token_length = 0;
	while(input_text[input_offset] != 0) {
		char current = input_text[input_offset++];
		line_pos++;
		if (is_delimiter(current)) {
			if (current == '\n') {
				line_no++;
				line_pos = 0;
			}

			if (token_length > 0) {
				break;
			} else {
				continue;
			}
		} else {
			current_token[token_length++] = current;
		}
	}

	if (token_length == 0) {
		free(current_token);
		current_token = NULL;
	} else {
		current_token[token_length] = 0;
	}

	return current_token;
}

void lexer_cleanup() {
	free(input_text);
	input_text = NULL;

	free(current_token);
	current_token = NULL;
}
