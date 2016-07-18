#pragma once


#include <string.h>
#include "natrix_object.h"

#define VALUE_NAME_MAX_SIZE (20)

typedef struct _Element {
    char name[VALUE_NAME_MAX_SIZE];
    Object *object;
    struct _Element *next;
} Element;


typedef struct _Namespace {
    Element *values;
    struct _Namespace *parent;
} Namespace;

void naInitElement(Element *element, char *name, Object *object);
void naInit(Namespace *ns, Namespace *parent);
void naPushElementE(Namespace *ns, char *name, Object *object);
Object * naFind(Namespace *ns, const char *name);
void naPrint(Namespace *ns);
