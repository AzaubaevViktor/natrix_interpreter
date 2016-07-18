//
// Created by ktulhy on 15.07.16.
//

#include "interpreter.h"


void _printStackObject(Interpreter *interpreter);
void _printNamespace(Interpreter *interpreter);

void initInterpreter(Interpreter *interpreter) {
    interpreter->PC = 0;
    interpreter->bytecodePos = 0;
    daInit(&interpreter->valuesStack);
    if check_err return;
    initNamespace(&interpreter->namespace, NULL);
    *(interpreter->builtins) = _printStackObject;
    *(interpreter->builtins + 1) = _printNamespace;
}

#define getBytecode() interpreter->bytecode[interpreter->PC++];

void step(Interpreter *interpreter) {
    uint8_t bytecode = getBytecode();
    switch (bytecode) {
        case NOP: {
            ++interpreter->PC;
            break;
        }
        case END: {
            natrix_error = END_BYTECODE_ERR;
            break;
        }
        case PUSH_VALUE: {
            uint8_t type = getBytecode();
            Object *object = newObject();
            if check_err return;
            object->type = type;

            switch (type) {
                case OBJECT_TYPE_LINT:
                    object->vLInt = *(int16_t *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(int16_t);
                    break;
                case OBJECT_TYPE_ULINT:
                    object->vULInt = *(uint16_t *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(uint16_t);
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

            daPush(&interpreter->valuesStack, object);
            break;
        }
        case CALL: {
            uint8_t number = getBytecode();
            interpreter->builtins[number](interpreter);
            break;
        }
        case STORE_VALUE: {
            Object *name = daPop(&interpreter->valuesStack);
            if check_err break;
            Object *obj = daPop(&interpreter->valuesStack);
            if check_err break;

            if (OBJECT_TYPE_STRING != name->type) {
                natrix_error = WRONG_VALUE_TYPE_ERR;
                break;
            }
            if (strlen(name->vString) > VALUE_NAME_MAX_SIZE) {
                natrix_error = VALUE_NAME_TOO_LONG_ERR;
                break;
            }
            pushElement(&interpreter->namespace, name->vString, obj);
            if check_err break;
            break;
        }
        default:
            natrix_error = UNKNOWN_BYTECODE;
            break;
    }
}

void _printStackObject(Interpreter *interpreter) {
    Object *object = daPop(&interpreter->valuesStack);
    if (!check_err) {
        printObjectInfo(object);
    }
    daPush(&interpreter->valuesStack, object);
}

void _printNamespace(Interpreter *interpreter) {
    printNamespace(&interpreter->namespace);
}