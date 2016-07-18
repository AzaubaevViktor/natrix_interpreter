//
// Created by ktulhy on 7/18/16.
//

#include "namespace.h"

void initElement(Element *element, char *name, Object* object) {
    strncpy(element->name, name, NAME_MAX_SIZE);
    element->object = object;
    element->next = NULL;
}

void initNamespace(Namespace *ns, Namespace *parent) {
    ns->values = NULL;
    ns->parent = parent;
}

void pushElement(Namespace *ns, Element *el) {
    if (!ns->values) {
        ns->values = el;
    } else {
        el->next = ns->values;
        ns->values = el;
    }
}

Element *insideFind(Namespace *ns, const char *name) {
    Element *el = ns->values;
    while (el) {
        if (0 == strncmp(el->name, name, NAME_MAX_SIZE)) {
            return el;
        }
        el = el->next;
    }
    return NULL;
}

Element *find(Namespace *ns, const char *name) {
    Element *el;
    while (ns) {
        el = insideFind(ns, name);
        if (el) {
            return el;
        }
        ns = ns->parent;
    }
    return NULL;
}

void printNamespace(Namespace *ns) {
    Element *el = ns->values;
    while (el) {
        printf("%s: ", el->name);
        printObjectInfo(el->object);
        el = el->next;
    }
}