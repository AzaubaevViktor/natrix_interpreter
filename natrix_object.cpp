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
            printf("LINT: `%li`\n", object->vLInt);
            break;
        case OBJECT_TYPE_ULINT:
            printf("ULINT: `%lu`\n", object->vULInt);
            break;
        case OBJECT_TYPE_DOUBLE:
            printf("LINT: `%lf`\n", object->vDouble);
            break;
        case OBJECT_TYPE_CHAR:
            printf("LINT: `%c`\n", object->vChar);
            break;

        default:
            printf("Unknown type of object\n");
            break;
    }
}