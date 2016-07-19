#pragma once


#include <string.h>
#include "natrix_object.h"

#define VALUE_NAME_MAX_SIZE (20)

typedef struct _Element {
    char name[VALUE_NAME_MAX_SIZE];
    Object *object;
    struct _Element *next;
} Element;


typedef struct _NativeDict {
    Element *values;
    struct _NativeDict *parent;
} NativeDict;

void ndInitElement(Element *element, char *name, Object *object);
void ndInit(NativeDict *ns, NativeDict *parent);
void ndPushElementE(NativeDict *ns, char *name, Object *object);
Object * ndFind(NativeDict *ns, const char *name);
void ndPrint(NativeDict *ns);
