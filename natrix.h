#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ERRORS

extern int natrix_error;

#define NO_ERR (0)
#define UNKNOWN_BYTECODE (1)
#define ALLOC_ERR (2)
#define UNKNOWN_VALUE_TYPE_ERR (3)
#define NO_VALUE_ERR (4)
#define INDEX_ERR (5)
#define END_BYTECODE_ERR (6)
#define WRONG_VALUE_TYPE_ERR (7)
#define VALUE_NAME_TOO_LONG_ERR (8)
#define OBJECT_NOT_IN_NAMESPACE_ERR (9)
#define INVALID_FIELD_NAME_ERR (10)

#define checkErr (NO_ERR != natrix_error)
#define check_end (END_BYTECODE_ERR == natrix_error)


// NATIVE DICT

#define VALUE_NAME_MAX_SIZE (20)

typedef struct _Element {
    char name[VALUE_NAME_MAX_SIZE];
    struct _Object *object;
    struct _Element *next;
} Element;


typedef struct _NativeDict {
    Element *values;
    struct _NativeDict *parent;
} NativeDict;

void ndInitElement(Element *element, char *name, struct _Object *object);
void ndInit(NativeDict *ns, NativeDict *parent);
void ndPushElementE(NativeDict *ns, char *name, struct _Object *object);
struct _Object * ndFind(NativeDict *ns, const char *name);
void ndPrint(NativeDict *ns);


// NATRIX OBJECT

#define OBJECT_TYPE_INT (0x1)
#define OBJECT_TYPE_DOUBLE (0x3)
#define OBJECT_TYPE_CHAR (0x4)
#define OBJECT_TYPE_STRING (0x5)

typedef struct _Object {
    unsigned int type;
    union {
        int32_t vInt;
        double vDouble;
        uint8_t vChar;
        char *vString;
    };
    struct _NativeDict fields;
} Object;

Object *newObjectE();
void printObjectInfo(Object *object);
int isInt(Object *object);
int isDouble(Object *object);

// NATIVE ARRAY

#define DYNAMIC_ARRAY_CHUNK_SIZE (16)

typedef struct _DynamicArray {
    Object **values; // Массив указателей на объекты
    uint16_t size;
    uint16_t len;
} DynamicArray;

void daInitE(DynamicArray *array);
void daCheckExtendE(DynamicArray *array);
void daPushE(DynamicArray *array, Object *obj);
Object *daPopE(DynamicArray *array);
Object *daGetE(DynamicArray *array, int32_t n);

// INTERPRETER


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
 * START_STACK -> ... -> obj_value -> var_name -> END_STACK
 */

#define GET_VALUE (0x6)
/*
 * Достаёт значение из namespace и кладёт в стек
 * START_STACK -> ... -> var_name -> END_STACK
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
#define MUNIS (0x9)
#define MUL (0xA)
#define DIV (0xB)
#define MOD (0xC)
#define STORE_FIELD (0xD)
/*
 * STORE_FIELD
 * Присваивает объект полю объекта
 * START_STACK -> ... -> obj_value -> field_name -> target_object -> END_STACK
 */
#define GET_FIELD (0xE)
/*
 * GET_FIELD
 * Возвращает на стек объект
 * START_STACK -> ... -> field_name -> target_object -> END_STACK
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
