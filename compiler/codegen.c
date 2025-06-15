#include "compiler.h"

void llvm_codegen(ast_root_t* root, FILE* output) {
	fprintf(output, "source_filename = \"%s\"\n\n", input_filename);
	fprintf(output, "define i32 @main() {\n");
	fprintf(output, "entry:\n");
	fprintf(output, "  ret i32 0\n");
	fprintf(output, "}\n");
}
