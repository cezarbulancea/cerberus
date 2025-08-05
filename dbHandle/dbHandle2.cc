#include "dbHandle.ih"

DbHandle::DbHandle(DbHandle &&tmp) noexcept
:
    d_db(exchange(tmp.d_db, nullptr))
{}