#ifndef INCLUDED_STATEMENT_
#define INCLUDED_STATEMENT_

#include <sqlite3.h>

struct Statement
{
    sqlite3_stmt *ptr = nullptr;

    Statement() = default;
    Statement(Statement const &other) = delete;
    Statement(Statement &&tmp);

    Statement &operator=(Statement const &other) = delete;
    Statement &operator=(Statement &&tmp);

    ~Statement();

    private:
        void reset();
};

#endif