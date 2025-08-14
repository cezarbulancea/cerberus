#ifndef INCLUDED_STATEMENT_
#define INCLUDED_STATEMENT_

#include <sqlite3.h>

/**
 * \brief RAII wrapper for an SQLite prepared statement (`sqlite3_stmt*`).
 *
 * Finalizes the statement in the destructor or on move-assignment of a new
 * handle. Copy is disabled because two owners finalizing the same statement
 * would be undefined behavior.
 */
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
        /** Finalize and reset `ptr` to nullptr. */
        void reset();
};

#endif