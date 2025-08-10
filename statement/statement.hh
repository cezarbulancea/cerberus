#ifndef INCLUDED_STATEMENT_
#define INCLUDED_STATEMENT_

#include <sqlite3.h>

struct Statement
{
    sqlite3_stmt *ptr = nullptr;

    ~Statement();
};

#endif