#include "dbHandle.ih"

DbHandle::DbHandle(string const &filename)
{   
    size_t flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX;
    if (sqlite3_open_v2(filename.c_str(), &d_db, flags, nullptr) != SQLITE_OK)
    {
        string const errorMessage = d_db ? 
            sqlite3_errmsg(d_db) : "sqlite3_open_v2 failed";
        if (d_db)
            sqlite3_close(d_db);
        throw runtime_error("Failed to open the database: " + errorMessage);
    }
}