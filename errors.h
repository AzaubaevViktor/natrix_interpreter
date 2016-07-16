#pragma once

extern int natrix_error;

#define NO_ERR (0)
#define UNKNOWN_BYTECODE (1)
#define ALLOC_ERR (2)
#define UNKNOWN_VALUE_TYPE_ERR (3)
#define NO_VALUE_ERR (4)
#define INDEX_ERR (5)
#define END_BYTECODE_ERR (6)

#define check_err (NO_ERR != natrix_error)
#define check_end (END_BYTECODE_ERR == natrix_error)