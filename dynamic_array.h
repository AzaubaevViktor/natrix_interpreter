#pragma once

#include <stdint.h>
#include "natrix_object.h"

#define DYNAMIC_ARRAY_CHUNK_SIZE (16)

typedef struct _DynamicArray {
    Object **values; // Массив указателей на объекты
    uint16_t size;
    uint16_t len;
} DynamicArray;

void daInit(DynamicArray *array);
void daCheckExtend(DynamicArray *array);
void daPush(DynamicArray *array, Object *obj);
Object *daPop(DynamicArray *array);
Object *daGet(DynamicArray *array, int32_t n);