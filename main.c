#include <stdio.h>
#include <string.h>
#include "natrix.h"
#include "bytecode_debug.h"


int main() {
    Interpreter interpreter;
    inInitE(&interpreter);
    uint8_t bytecode[] = "\x02\x01\x10\x00\x00\x00"
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
            "\x02\x05\x0BPlus 100 = "
            "\x07"
            "\x02\x01\x64\x00\x00\x00"
            "\x08"
            "\xCA\x00"
            "\xED";
    printBytecode(bytecode);
    memcpy(interpreter.bytecode, bytecode, sizeof(bytecode));
    /*
     * PUSH_VALUE OBJECT_TYPE_INT 16
     * CALL 0 // printStackObject
     * PUSH_VALUE OBJECT_TYPE_STRING 5 'hello'
     * CALL 0 // printStackObject
     * PUSH_VALUE OBJECT_TYPE_STRING 1 '\n'
     * PRINT_STR
     * STORE_VALUE
     * CALL 1 // ndPrint
     * PUSH_VALUE OBJECT_TYPE_STRING 5 'hello'
     * GET_VALUE
     * CALL 0
     * PUSH_VALUE OBJECT_TYPE_STRING 1 '\n'
     * PRINT_STR
     * PUSH_VALUE OBJECT_TYPE_STRING B 'Plus 100 = '
     * PRINT_STR
     * PUSH_VALUE OBJECT_TYPE_INT 100
     * PLUS
     * CALL 0
     * END
     */
    while (1) {
        inStepE(&interpreter);
        if (check_err || check_end) {
            printf("Natrix error: %d\n", natrix_error);
            break;
        }
    }

    return 0;
}