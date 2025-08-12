#include "statement.ih"

void Statement::reset()
{
    if (ptr) 
    {
        sqlite3_finalize(ptr); 
        ptr = nullptr;
    }
}