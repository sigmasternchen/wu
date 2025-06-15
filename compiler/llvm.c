#include "compiler.h"

#include <unistd.h>

static int pipe_fds[] = {-1, -1};
static pid_t child = 0;

FILE* get_ir_pipe() {
	if (pipe(pipe_fds) < 0) {
		panic("get_ir_pipe");
	}

	FILE* write_end = fdopen(pipe_fds[1], "w");
	if (write_end == NULL) {
		panic("get_ir_pipe");
	}

	return write_end;
}

void call_llvm(const char* output_filename) {
	child = fork();
	if (child == -1) {
		panic("fork");
	} else if (child == 0) {
		close(pipe_fds[1]);

		if (dup2(pipe_fds[0], STDIN_FILENO) < 0) {
			panic("call_llvm (input)");
		}

		close(pipe_fds[0]);

		if (execlp("llc", "llc", "-filetype=obj", "-o", output_filename, NULL) < 0) {
			panic("call llvm");
		}
	} else {
		close(pipe_fds[0]);
	}
}

void wait_for_llvm() {
	int status;
	waitpid(child, &status, 0);

	int exit_code = WEXITSTATUS(status);
	if (exit_code != 0) {
		llvm_error("llc exited with non-zero exit code: %d", exit_code);
	}	
}

