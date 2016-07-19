#include <stdint.h>
#include "bytecode_debug.h"

#define next() (PC++, curSym++)
#define nextTo(v) (PC += (v), curSym += (v))
#define printPC() printf("%-6d ", PC)

void printBytecode(uint8_t *bytecode) {
    int PC = 0;
    uint8_t *curSym = bytecode;

    while (*curSym != END && !checkErr) {
        printPC();
        uint8_t code = *curSym;
        next();
    
        switch (code) {
            case NOP:
                printf("NOP");
                break;

            case END:
                // Никогда сюда никто не зайдёт(
                printf("END");
                break;

            case PUSH_VALUE: {
                printf("PUSH_VALUE ");

                Object *object = newObjectE();
                object->type = *curSym;
                next();

                switch (object->type) {
                    case OBJECT_TYPE_INT:
                        object->vInt = *(int32_t *) (bytecode + PC);
                        nextTo(sizeof(int32_t));
                        break;
                    case OBJECT_TYPE_DOUBLE:
                        object->vDouble = *(double *) (bytecode + PC);
                        nextTo(sizeof(double));
                        break;
                    case OBJECT_TYPE_CHAR:
                        object->vChar = (uint8_t) (bytecode + PC);
                        nextTo(sizeof(uint8_t));
                        break;
                    case OBJECT_TYPE_STRING: {
                        uint8_t len = *curSym;
                        next();
                        object->vString = malloc(sizeof(uint8_t) * (len + 1));
                        for (uint8_t i = 0; i < len; ++i) {
                            object->vString[i] = *curSym;
                            next();
                        }
                        object->vString[len] = '\0';
                        break;
                    }
                    default:
                        natrix_error = UNKNOWN_VALUE_TYPE_ERR;
                }
                printf("(");
                printObjectInfo(object);
                printf(")");
                if checkErr break;

                break;
            }
            case CALL: {
                uint8_t number = *curSym;
                next();

                printf("CALL %d", number);
                break;
            }
            case STORE_VALUE:
                printf("STORE_VALUE");
                break;

            case GET_VALUE:
                printf("GET_VALUE");
                break;

            case PRINT_STR:
                printf("PRINT_STR");
                break;

            case PLUS:
                printf("PLUS");
                break;

            case STORE_FIELD:
                printf("STORE_FIELD");
                break;

            case GET_FIELD:
                printf("GET_FIELD");
                break;

            default:
                natrix_error = UNKNOWN_BYTECODE;
                break;
        }

        printf("\n");
    }
    if checkErr {
        printf("Natrix bytecode parse error: %d\n", natrix_error);
        natrix_error = 0;
    } else {
        printPC();
        printf("END\n");
    }
}