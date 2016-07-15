#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

#define OBJECT_TYPE_LINT (1)
#define OBJECT_TYPE_ULINT (2)
#define OBJECT_TYPE_DOUBLE (3)
#define OBJECT_TYPE_CHAR (4)

typedef struct _Object {
    unsigned int type;
    union {
//        long int vLInt;
//        unsigned long int vULInt;
        int vLInt;
        unsigned int vULInt;
        double vDouble;
        char vChar;
    };
} Object;

Object *newObject();
void printObjectInfo(Object *object);