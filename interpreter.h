#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "natrix_object.h"
#include "errors.h"

#define PUSH_VALUE (1)
#define POP_VALUE (2)
#define PUSH_ARG (3)
#define CLEAR_ARGS (4)
#define CALL_BUILTIN (5)


typedef struct _Interpreter {
    u_char bytecode[100];
    int bytecodePos;
    int PC;
    Object *valuesStack[100];
    int valuesI;
    Object *argsStack[100];
    int argsI;
    void (*builtins[10])(struct _Interpreter *);
} Interpreter;

void initInterpreter(Interpreter *interpreter);
void step(Interpreter *interpreter);
