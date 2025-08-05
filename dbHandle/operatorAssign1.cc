#include "dbHandle.ih"

DbHandle &DbHandle::operator=(DbHandle &&tmp) noexcept
{
    if (this != &tmp)
    {
        if (d_db)
            sqlite3_close(d_db);
        d_db = exchange(tmp.d_db, nullptr);
    }
    
    return *this;
}