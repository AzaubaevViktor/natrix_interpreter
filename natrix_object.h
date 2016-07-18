#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "errors.h"

#define OBJECT_TYPE_INT (0x1)
#define OBJECT_TYPE_DOUBLE (0x3)
#define OBJECT_TYPE_CHAR (0x4)
#define OBJECT_TYPE_STRING (0x5)

typedef struct _Object {
    unsigned int type;
    union {
        int16_t vInt;
        double vDouble;
        uint8_t vChar;
        char *vString;
    };
} Object;

Object *newObjectE();
void printObjectInfo(Object *object);
int isInt(Object *object);
int isDouble(Object *object);
