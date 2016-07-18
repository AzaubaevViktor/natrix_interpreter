#pragma once


#include <string.h>
#include "natrix_object.h"

#define NAME_MAX_SIZE (20)

typedef struct _Element {
    char name[NAME_MAX_SIZE];
    Object *object;
    struct _Element *next;
} Element;


typedef struct _Namespace {
    Element *values;
    struct _Namespace *parent;
} Namespace;

void initElement(Element *element, char *name, Object* object);
void initNamespace(Namespace *ns, Namespace *parent);
void pushElement(Namespace *ns, Element *el);
Element *find(Namespace *ns, const char *name);
void printNamespace(Namespace *ns);
