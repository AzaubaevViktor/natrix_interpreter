#pragma once

extern int natrix_error;

#define NO_ERR (0)
#define NO_ARG_ERR (1)
#define UNKNOWN_BYTECODE (2)
#define ALLOC_ERR (3)
#define UNKNOWN_VALUE_TYPE_ERR (4)
#define NO_VALUE_ERR (5)

#define check_err (NO_ERR != natrix_error)