# wuc - wu compiler

This document provides essential information about the wuc compiler, which compiles programs written in the wu programming language.

## Overview

The wuc compiler takes a wu source file as input and generates an object file that can be linked into an executable. The output file will have the same name as the input file but with a `.o` extension. You can also specify a custom output file name using the `-o` flag.

## Building wuc

To build wuc, just use the provided Makefile.

```bash
make all
```

Please note that you will need LLVM (llc, clang) to build wuc.

## Usage

To compile a wu source file, use the following command:

```bash
./wuc program.wu
```

This command will generate an object file named `program.o`. You can than use `clang` (or any other linker of your choice) to create an executable file.

```bash
clang -o program program.o
./program
```

### Custom Output File

If you want to specify a different name for the output file, you can use the `-o` flag:

```bash
./wuc -o output.o input.wu
```

In this case, the compiled object file will be named `output.o`.

### Help Option

For help and usage information, you can use the `-h` flag:

```bash
./wuc -h
```

This will display the following help message:

```
Usage: ./wuc [-o OUTPUT] INPUT
  INPUT       The wu source file to compile.
  -o OUTPUT   The compiled object file (optional).
              If not provided, OUTPUT will be INPUT with .o extension.
  -h          Show this help message.
```

