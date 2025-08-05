#include "dbHandle.ih"

DbHandle::operator sqlite3*() const noexcept
{
    return d_db;
}