#include "dbHandle.ih"

DbHandle::~DbHandle()
{
    if (d_db)
        sqlite3_close(d_db);
}