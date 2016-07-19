//
// Created by ktulhy on 15.07.16.
//

#include "interpreter.h"


void _printStackObject(Interpreter *interpreter);
void _printNamespace(Interpreter *interpreter);

void inInitE(Interpreter *interpreter) {
    interpreter->PC = 0;
    interpreter->bytecodePos = 0;
    daInitE(&interpreter->valuesStack);
    if check_err return;
    ndInit(&interpreter->namespace, NULL);
    *(interpreter->builtins) = _printStackObject;
    *(interpreter->builtins + 1) = _printNamespace;
}

#define getBytecode() interpreter->bytecode[interpreter->PC++];

Object *inGetStrFromStackE(Interpreter *interpreter) {
    Object *strObj = daPopE(&interpreter->valuesStack);
    if check_err return NULL;
    if (OBJECT_TYPE_STRING != strObj->type) {
        natrix_error = WRONG_VALUE_TYPE_ERR;
        return NULL;
    }
    return strObj;
}

void inStepE(Interpreter *interpreter) {
    uint8_t bytecode = getBytecode();
    switch (bytecode) {
        case NOP: {
            break;
        }
        case END: {
            natrix_error = END_BYTECODE_ERR;
            break;
        }
        case PUSH_VALUE: {
            uint8_t type = getBytecode();
            Object *object = newObjectE();
            if check_err return;
            object->type = type;

            switch (type) {
                case OBJECT_TYPE_INT:
                    object->vInt = *(int32_t *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(int32_t);
                    break;
                case OBJECT_TYPE_DOUBLE:
                    object->vDouble = *(double *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(double);
                    break;
                case OBJECT_TYPE_CHAR:
                    object->vChar = *(uint8_t *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(uint8_t);
                    break;
                case OBJECT_TYPE_STRING: {
                    uint8_t len = getBytecode();
                    object->vString = malloc(sizeof(uint8_t) * (len + 1));
                    for (uint8_t i = 0; i < len; ++i) {
                        object->vString[i] = getBytecode();
                    }
                    object->vString[len] = '\0';
                    break;
                }
                default:
                    natrix_error = UNKNOWN_VALUE_TYPE_ERR;
            }
            if check_err break;

            daPushE(&interpreter->valuesStack, object);
            break;
        }
        case CALL: {
            uint8_t number = getBytecode();
            interpreter->builtins[number](interpreter);
            break;
        }
        case STORE_VALUE: {
            Object *name = inGetStrFromStackE(interpreter);
            if check_err break;
            Object *obj = daPopE(&interpreter->valuesStack);
            if check_err break;

            if (strlen(name->vString) > VALUE_NAME_MAX_SIZE) {
                natrix_error = VALUE_NAME_TOO_LONG_ERR;
                break;
            }
            ndPushElementE(&interpreter->namespace, name->vString, obj);
            if check_err break;
            break;
        }
        case GET_VALUE: {
            Object *name = inGetStrFromStackE(interpreter);
            if check_err break;
            Object *obj = ndFind(&interpreter->namespace, name->vString);
            if (!obj) {
                natrix_error = OBJECT_NOT_IN_NAMESPACE;
                break;
            }
            daPushE(&interpreter->valuesStack, obj);
            break;
        }
        case PRINT_STR: {
            Object *name = inGetStrFromStackE(interpreter);
            if check_err break;

            printf("%s", name->vString);
            break;
        }
        case PLUS: {
            Object *obj2 = daPopE(&interpreter->valuesStack);
            if check_err break;
            Object *obj1 = daPopE(&interpreter->valuesStack);
            if check_err break;
            Object *result = newObjectE();
            if check_err break;

            if (isInt(obj1) && isInt(obj2)) {
                result->type = OBJECT_TYPE_INT;
                result->vInt = obj1->vInt + obj2->vInt;
                daPushE(&interpreter->valuesStack, result);
            } else if (isDouble(obj1) || isDouble(obj2)) {
                result->type = OBJECT_TYPE_DOUBLE;
                result->vDouble = isDouble(obj1) ? obj1->vDouble : obj1->vInt;
                result->vDouble += isDouble(obj2) ? obj2->vDouble : obj2->vInt;
                daPushE(&interpreter->valuesStack, result);
            } else {
                natrix_error = WRONG_VALUE_TYPE_ERR;
            }
            break;
        }
        default:
            natrix_error = UNKNOWN_BYTECODE;
            break;
    }
}

void _printStackObject(Interpreter *interpreter) {
    Object *object = daPopE(&interpreter->valuesStack);
    if (!check_err) {
        printObjectInfo(object);
    }
    daPushE(&interpreter->valuesStack, object);
}

void _printNamespace(Interpreter *interpreter) {
    ndPrint(&interpreter->namespace);
}