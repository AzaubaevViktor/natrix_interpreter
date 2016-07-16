//
// Created by ktulhy on 15.07.16.
//

#include "interpreter.h"


void printInfo(Interpreter *interpreter);

void initInterpreter(Interpreter *interpreter) {
    interpreter->PC = 0;
    interpreter->bytecodePos = 0;
    daInit(&interpreter->valuesStack);
    *(interpreter->builtins) = printInfo;
}

#define getBytecode() interpreter->bytecode[interpreter->PC++];

void step(Interpreter *interpreter) {
    u_char bytecode = getBytecode();
    switch (bytecode) {
        case END: {
            natrix_error = END_BYTECODE_ERR;
            break;
        }
        case PUSH_VALUE: {
            u_char type = getBytecode();
            Object *object = newObject();
            if check_err return;
            object->type = type;

            switch (type) {
                case OBJECT_TYPE_LINT:
                    object->vLInt = *(int *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(int);
                    break;
                case OBJECT_TYPE_ULINT:
                    object->vULInt = *(u_int *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(u_int);
                    break;
                case OBJECT_TYPE_DOUBLE:
                    object->vDouble = *(double *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(double);
                    break;
                case OBJECT_TYPE_CHAR:
                    object->vChar = *(char *) (interpreter->bytecode + interpreter->PC);
                    interpreter->PC += sizeof(char);
                    break;
                default:
                    natrix_error = UNKNOWN_VALUE_TYPE_ERR;
            }
            if check_err break;

            daPush(&interpreter->valuesStack, object);
            break;
        }
        case CALL: {
            u_char number = getBytecode();
            interpreter->builtins[number](interpreter);
            break;
        }
        default:
            natrix_error = UNKNOWN_BYTECODE;
            break;
    }
}

void printInfo(Interpreter *interpreter) {
    Object *object = daPop(&interpreter->valuesStack);
    if (!check_err) {
        printObjectInfo(object);
    }
}