#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "errors.h"

#define OBJECT_TYPE_LINT (1)
#define OBJECT_TYPE_ULINT (2)
#define OBJECT_TYPE_DOUBLE (3)
#define OBJECT_TYPE_CHAR (4)

typedef struct _Object {
    unsigned int type;
    union {
        int16_t vLInt;
        uint16_t vULInt;
        double vDouble;
        uint8_t vChar;
    };
} Object;

Object *newObject();
void printObjectInfo(Object *object);