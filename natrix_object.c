//
// Created by ktulhy on 15.07.16.
//

#include "natrix_object.h"

Object *newObject() {
    Object *object = (Object *) calloc(1, sizeof(Object));
    if (!object) {
        natrix_error = ALLOC_ERR;
    }
    return object;
}

void printObjectInfo(Object *object) {
    switch (object->type) {
        case OBJECT_TYPE_LINT:
            printf("LINT: `%hi`", object->vLInt);
            break;
        case OBJECT_TYPE_ULINT:
            printf("ULINT: `%hu`", object->vULInt);
            break;
        case OBJECT_TYPE_DOUBLE:
            printf("LINT: `%lf`", object->vDouble);
            break;
        case OBJECT_TYPE_CHAR:
            printf("LINT: `%c`", object->vChar);
            break;
        case OBJECT_TYPE_STRING:
            printf("STRING: `%s`", object->vString);
            break;
        default:
            printf("Unknown type of object");
            break;
    }
}