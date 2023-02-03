# Tiny C Compiler

## Introduction

Our goal is to build a bootstrapping (being able to compile itself) compiler for a subset of C language. 
We would expect our compiler to translate C programs into corresponding assembly codes and detect syntax error during the process.
As we progress, we would expand the supported syntax and make the resulting language more powerful.

### Current Progress

|   Date   |   Progress   |
| -------- | ------------ |
| 02/02/23 | `while` Loop |
| 01/31/23 | `if` Statements |
| 01/30/23 | Comparison Operators |
| 01/29/23 | Global Variables |
| 01/28/23 | Statements |
| 01/25/23 | Operator Procedence; Assembly |
| 01/24/23 | Lexical Scanning; Parsing |

## Setting Up the Development Environment

This project runs on Ubuntu 22.04 with Intel x86-64 architecture.
To run on ARM64-based Apple silicon, install UTM to emulate a x86-64 hardware platform.

Once we have the desired platform, we are going to need an existing C compiler.
Install the essential building package with the following command:

```
  $ sudo apt-get install build-essential
```

## Testing

The testing input files and the expected outputs are in the `tests/` directory.
Running `make test` in the terminal would go into this directory, 
compile each input using the tiny compiler we wrote, 
and compare the outputs against the expected outputs.

```
cc -o comp1 -g cg.c decl.c expr.c gen.c main.c misc.c scan.c stmt.c
      sym.c tree.c
(cd tests; chmod +x runtests; ./runtests)
input01: OK
input02: OK
input03: OK
input04: OK
input05: OK
input06: OK
```
