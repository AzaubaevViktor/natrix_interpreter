//
// Created by ktulhy on 15.07.16.
//

#include "natrix.h"


void _printStackObject(Interpreter *interpreter);
void _printNamespace(Interpreter *interpreter);

void inInitE(Interpreter *interpreter) {
    interpreter->PC = 0;
    interpreter->bytecodePos = 0;
    daInitE(&interpreter->valuesStack);
    if checkErr return;
    ndInit(&interpreter->namespace, NULL);
    *(interpreter->builtins) = _printStackObject;
    *(interpreter->builtins + 1) = _printNamespace;
}

#define getBytecode() interpreter->bytecode[interpreter->PC++];

#define popStackE() daPopE(&interpreter->valuesStack)

#define popStrStackE() _popStrStackE(interpreter)

#define pushStackE(obj) daPushE(&interpreter->valuesStack, (obj))

Object *_popStrStackE(Interpreter *interpreter) {
    Object *strObj = popStackE();
    if checkErr return NULL;
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
            if checkErr return;
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
            if checkErr break;

            pushStackE(object);
            break;
        }
        case CALL: {
            uint8_t number = getBytecode();
            interpreter->builtins[number](interpreter);
            break;
        }
        case STORE_VALUE: {
            Object *varName = popStrStackE();
            if checkErr break;
            Object *objValue = popStackE();
            if checkErr break;

            if (strlen(varName->vString) > VALUE_NAME_MAX_SIZE) {
                natrix_error = VALUE_NAME_TOO_LONG_ERR;
                break;
            }
            ndPushElementE(&interpreter->namespace, varName->vString, objValue);
            if checkErr break;
            break;
        }
        case GET_VALUE: {
            Object *varName = popStrStackE();
            if checkErr break;
            Object *objValue = ndFind(&interpreter->namespace, varName->vString);
            if (!objValue) {
                natrix_error = OBJECT_NOT_IN_NAMESPACE_ERR;
                break;
            }
            pushStackE(objValue);
            break;
        }
        case PRINT_STR: {
            Object *strObj = popStrStackE();
            if checkErr break;

            printf("%s", strObj->vString);
            break;
        }
        case PLUS: {
            Object *right = popStackE();
            if checkErr break;
            Object *left = popStackE();
            if checkErr break;
            Object *result = newObjectE();
            if checkErr break;

            if (isInt(left) && isInt(right)) {
                result->type = OBJECT_TYPE_INT;
                result->vInt = left->vInt + right->vInt;
                pushStackE(result);
            } else if (isDouble(left) || isDouble(right)) {
                result->type = OBJECT_TYPE_DOUBLE;
                result->vDouble = isDouble(left) ? left->vDouble : left->vInt;
                result->vDouble += isDouble(right) ? right->vDouble : right->vInt;
                pushStackE(result);
            } else {
                natrix_error = WRONG_VALUE_TYPE_ERR;
            }
            break;
        }
        case STORE_FIELD: {
            Object *targetObject = popStackE();
            if checkErr break;
            Object *fieldName = popStrStackE();
            if checkErr break;
            Object *objValue = popStackE();
            if checkErr break;

            ndPushElementE(&targetObject->fields,
                           fieldName->vString,
                           objValue
            );
            break;
        }
        case GET_FIELD: {
            Object *targetObject = popStackE();
            if checkErr break;
            Object *fieldName = popStrStackE();
            if checkErr break;

            Object *objValue = ndFind(
                    &targetObject->fields,
                    fieldName->vString
            );

            if (!objValue) {
                natrix_error = INVALID_FIELD_NAME_ERR;
                break;
            }

            pushStackE(objValue);
            if checkErr break;
            break;
        }
        default:
            natrix_error = UNKNOWN_BYTECODE;
            break;
    }
}

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void _printStackObject(Interpreter *interpreter) {
    printf(RED "\nDEBUG PRINT LAST STACK\n");
    Object *object = popStackE();
    if (!checkErr) {
        printObjectInfo(object);
    }
    pushStackE(object);
    printf("\nEND DEBUG\n" RESET);
}

void _printNamespace(Interpreter *interpreter) {
    printf(RED "\nDEBUG PRINT NAMESPACE\n");
    ndPrint(&interpreter->namespace);
    printf("\nEND DEBUG\n" RESET);
}

#undef popStackE