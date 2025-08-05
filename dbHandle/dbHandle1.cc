#include "dbHandle.ih"

DbHandle::DbHandle(string const &filename)
{                                      // Open (or create) the database
    if (sqlite3_open(filename.c_str(), &d_db) != SQLITE_OK)
    {
        string const errorMessage = sqlite3_errmsg(d_db);
        sqlite3_close(d_db);
        throw runtime_error("Failed to open the database: " + errorMessage);
    }
}