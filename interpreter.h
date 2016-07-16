#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "natrix_object.h"
#include "errors.h"

#define PUSH_VALUE (1)
/*
 * PUSH_VALUE (TYPE 1b) (VALUE ?b)
 * Загружает объект нужного типа в values
 */
#define POP_VALUE (2)
#define CALL (3)
/*
 * CALL (NUMBER 1b)
 * Вызывает функцию под номером
 */
#define STORE_VALUE (4)
/*
 * STORE_VALUE (NUMBER 1b)
 * Берёт из value и сохраняет в namespace под нужным номером
 */



typedef struct _Interpreter {
    u_char bytecode[100];
    int bytecodePos;
    int PC;
    Object *valuesStack[100];
    int valuesI;
    void (*builtins[10])(struct _Interpreter *);
} Interpreter;

void initInterpreter(Interpreter *interpreter);
void step(Interpreter *interpreter);
