#include "compiler.h"

#include <unistd.h>

const char* input_filename = NULL;
char* output_filename = NULL;

void pipeline() {
	FILE* input_file = fopen(input_filename, "r");
	if (input_file == NULL) {
		panic("input file");
	}

	debug("Lexer init", NULL);
	lexer_init(input_file);
	debug("Parser call", NULL);
	ast_root_t* ast = parse();
	debug("Lexer cleanup", NULL);
	lexer_cleanup();
	fclose(input_file);

	debug("LLVM IR pipe", NULL);
	FILE* ir_pipe = get_ir_pipe();
	
	debug("LLVM async call", NULL);
	call_llvm(output_filename);
	debug("Codegen call", NULL);
	llvm_codegen(ast, ir_pipe);

	fflush(ir_pipe);
	fclose(ir_pipe);

	debug("LLVM cleanup", NULL);
	wait_for_llvm();

	free(ast);

	debug("done", NULL);
}

void print_help(const char *program_name) {
	printf("Usage: %s [-o OUTPUT] INPUT\n", program_name);
	printf("  INPUT       The wu source file to compile.\n");
	printf("  -o OUTPUT   The compiled object file (optional).\n");
	printf("              If not provided, OUTPUT will be INPUT with .o extension.\n");
	printf("  -h          Show this help message.\n");
}

void build_output_filename() {
	output_filename = malloc(strlen(input_filename) + 3);
	if (output_filename == NULL) {
		panic("args");
	}
	strcpy(output_filename, input_filename);
	char *dot = strrchr(output_filename, '.');
	if (dot != NULL) {
		*dot = 0;
	}
	strcat(output_filename, ".o");
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Error: Missing INPUT argument.\n");
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	int opt;
	while ((opt = getopt(argc, argv, "ho:")) != -1) {
		switch (opt) {
			case 'o':
				output_filename = strdup(optarg);
				if (output_filename == NULL) {
					panic("strdup");
				}
				break;
			case 'h':
				print_help(argv[0]);
				return EXIT_SUCCESS;
			default:
				fprintf(stderr, "Error: Unknown option.\n");
				print_help(argv[0]);
				return EXIT_FAILURE;
		}
	}

	if (optind < argc) {
		input_filename = argv[optind];
	} else {
		fprintf(stderr, "Error: Missing INPUT argument.\n");
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	if (output_filename == NULL) {
		build_output_filename();
	}

	pipeline();

	return 0;
}
