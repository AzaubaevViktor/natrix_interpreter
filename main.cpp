#include <iostream>
#include <cstring>
#include "interpreter.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    Interpreter interpreter;
    initInterpreter(&interpreter);
    memcpy(interpreter.bytecode, "\x01\x01\x01\x00\x00\x00\x03\x00\x00", 9);
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