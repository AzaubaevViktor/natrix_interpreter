#include <stdio.h>
#include <string.h>
#include "interpreter.h"


int main() {
    Interpreter interpreter;
    initInterpreter(&interpreter);
    char bytecode[] = "\x02\x01\x10\x00\x00\x00"
            "\xCA\x00"
            "\x02\x05\x05hello"
            "\xCA\x00"
            "\x02\x05\x01\n"
            "\x07"
            "\x05"
            "\xCA\x01"
            "\x02\x05\x05hello"
            "\x06"
            "\xCA\x00"
            "\x02\x05\x01\n"
            "\x07"
            "\xED";
    memcpy(interpreter.bytecode, bytecode, sizeof(bytecode));
    /*
     * PUSH_VALUE OBJECT_TYPE_LINT 16
     * CALL 0 // printStackObject
     * PUSH_VALUE OBJECT_TYPE_STRING 5 'hello'
     * CALL 0 // printStackObject
     * PUSH_VALUE OBJECT_TYPE_STRING 1 '\n'
     * PRINT_STR
     * STORE_VALUE
     * CALL 1 // printNamespace
     * PUSH_VALUE OBJECT_TYPE_STRING 5 'hello'
     * GET_VALUE
     * CALL 0
     * PUSH_VALUE OBJECT_TYPE_STRING 1 '\n'
     * PRINT_STR
     * END
     */
    while (1) {
        step(&interpreter);
        if (check_err || check_end) {
            printf("Natrix error: %d\n", natrix_error);
            break;
        }
    }

    return 0;
}