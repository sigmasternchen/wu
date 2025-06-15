#include "compiler.h"

ast_root_t* parse() {
	ast_root_t* root = malloc(sizeof(ast_root_t));

	char* token = next_token();

	if (token != NULL) {
		parse_error("Unknown token '%s' at %zu:%zu", token, line_no, line_pos - strlen(token));
	}

	return root;
}
