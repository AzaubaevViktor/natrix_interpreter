#include <iostream>
#include <cstring>
#include "interpreter.h"


int main() {
    Interpreter interpreter;
    initInterpreter(&interpreter);
    memcpy(interpreter.bytecode, "\x02\x01\x01\x00\x00\x00\x04\x00\xFE", 9);
    /*
     * PUSH_VALUE OBJECT_TYPE_LINT 1
     * CALL 0
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