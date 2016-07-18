#pragma once

#include <stdint.h>
#include "natrix_object.h"

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