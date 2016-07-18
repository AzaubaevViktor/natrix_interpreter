#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "errors.h"

#define OBJECT_TYPE_LINT (0x1)
#define OBJECT_TYPE_ULINT (0x2)
#define OBJECT_TYPE_DOUBLE (0x3)
#define OBJECT_TYPE_CHAR (0x4)
#define OBJECT_TYPE_STRING (0x5)

typedef struct _Object {
    unsigned int type;
    union {
        int16_t vLInt;
        uint16_t vULInt;
        double vDouble;
        uint8_t vChar;
        uint8_t *vString;
    };
} Object;

Object *newObject();
void printObjectInfo(Object *object);