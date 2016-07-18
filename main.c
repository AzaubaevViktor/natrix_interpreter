#include <stdio.h>
#include <string.h>
#include "interpreter.h"


int main() {
    Interpreter interpreter;
    initInterpreter(&interpreter);
    char bytecode[] = "\x02\x01\x01\x00\x00\x00"
            "\x04\x00"
            "\x02\x05\x05hello"
            "\x04\x00"
            "\x05"
            "\x04\x01"
            "\xFE";
    memcpy(interpreter.bytecode, bytecode, sizeof(bytecode));
    /*
     * PUSH_VALUE OBJECT_TYPE_LINT 1
     * CALL 0 // printStackObject
     * PUSH_VALUE OBJECT_TYPE_STRING 5 'hello'
     * CALL 0 // printStackObject
     * STORE_VALUE
     * CALL 1 // printNamespace
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