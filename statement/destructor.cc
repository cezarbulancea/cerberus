#include "statement.ih"

Statement::~Statement()
{
    if (ptr)
        sqlite3_finalize(ptr);
}