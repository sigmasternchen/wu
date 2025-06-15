#ifndef COMPILER_H
#define COMPILER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define make_bold_red(text) "\e[1;31m" text "\e[0m"
#define make_blue(text) "\e[0;34m" text "\e[0m"
#define error(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define parse_error(format, ...) error(make_bold_red("Parse Error:") " " format "\n", __VA_ARGS__)
#define llvm_error(format, ...) error(make_bold_red("LLVM Error:") " " format "\n", __VA_ARGS__)
#define debug(format, ...) fprintf(stderr, make_blue("Debug: ") " " format "\n", __VA_ARGS__)
#define panic(location) error(make_bold_red("PANIC!") " %s: %s\n", location, strerror(errno))


extern size_t line_no;
extern size_t line_pos;
void lexer_init(FILE*);
char* next_token();
void lexer_cleanup();


typedef struct {
} ast_root_t;

ast_root_t* parse();

extern const char* input_filename;
void llvm_codegen(ast_root_t*, FILE*);


FILE* get_ir_pipe();
void call_llvm(const char*);
void wait_for_llvm();

#endif
