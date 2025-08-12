#include "statement.ih"

Statement &Statement::operator=(Statement &&tmp)
{
    if (this != &tmp) 
    {
        reset();
        ptr = tmp.ptr;
        tmp.ptr = nullptr;
    }

    return *this;
}