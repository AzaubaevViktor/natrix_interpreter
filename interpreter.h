#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "natrix_object.h"
#include "errors.h"
#include "dynamic_array.h"
#include "native_dict.h"

#define NOP (0x0)
/*
 * Пустая инструкция
 */

#define END (0xED)
/*
 * Конец байткода
 */

#define PUSH_VALUE (0x2)
/*
 * PUSH_VALUE (TYPE 1b) (VALUE ?b)
 * Загружает объект нужного типа в values
 */

#define POP_VALUE (0x3)

#define CALL (0xCA)
/*
 * CALL (NUMBER 1b)
 * Вызывает функцию под номером
 */

#define STORE_VALUE (0x5)
/*
 * STORE_VALUE
 * Берёт имя и значение из стека и сохраняет в текущий namespace
 * START_STACK -> ... -> obj -> name -> END_STACK
 */

#define GET_VALUE (0x6)
/*
 * Достаёт значение из namespace и кладёт в стек
 */

#define PRINT_STR (0x7)
/*
 * Печатает последний объект со стека
 * Как будто __str__, которого нет
 */

#define PLUS (0x8)
/*
 * Берёт два объекта со стека и складывает их;
 * Резульат кладёт на стек
 */


typedef struct _Interpreter {
    uint8_t bytecode[128];
    int bytecodePos;
    int PC;

    DynamicArray valuesStack;

    NativeDict namespace;

    void (*builtins[10])(struct _Interpreter *);
} Interpreter;

void inInitE(Interpreter *interpreter);
void inStepE(Interpreter *interpreter);
