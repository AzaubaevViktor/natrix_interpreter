#include <iostream>
#include <cstring>
#include "interpreter.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    Interpreter interpreter;
    initInterpreter(&interpreter);
    memcpy(interpreter.bytecode, "\x01\x01\x01\x00\x00\x00\x03\x05\x00", 9);
    /*
     * PUSH_VALUE OBJECT_TYPE_LINT 1
     * PUSH_ARG
     * CALL_BUILTIN 0
     */
    while (1) {
        step(&interpreter);
        if (natrix_error) {
            printf("Natrix error: %d\n", natrix_error);
            break;
        }
    }

    return 0;
}