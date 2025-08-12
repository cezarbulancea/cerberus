#include "statement.ih"

Statement::Statement(Statement &&tmp)
:
    ptr(tmp.ptr)
{
    tmp.ptr = nullptr;
}