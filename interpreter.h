#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "natrix_object.h"
#include "errors.h"
#include "dynamic_array.h"

#define NOP (0x0)
/*
 * Пустая инструкция
 */

#define END (0xFE)
/*
 * Конец байткода
 */

#define PUSH_VALUE (0x2)
/*
 * PUSH_VALUE (TYPE 1b) (VALUE ?b)
 * Загружает объект нужного типа в values
 */

#define POP_VALUE (0x3)

#define CALL (0x4)
/*
 * CALL (NUMBER 1b)
 * Вызывает функцию под номером
 */

#define STORE_VALUE (0x5)
/*
 * STORE_VALUE (NUMBER 1b)
 * Берёт из value и сохраняет в namespace под нужным номером
 */



typedef struct _Interpreter {
    uint8_t bytecode[100];
    int bytecodePos;
    int PC;

    DynamicArray valuesStack;

    void (*builtins[10])(struct _Interpreter *);
} Interpreter;

void initInterpreter(Interpreter *interpreter);
void step(Interpreter *interpreter);
