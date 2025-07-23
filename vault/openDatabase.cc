#include "vault.ih"

void Vault::openDatabase(string const &filename)
{                                      // Open (or create) the database
    if (sqlite3_open(filename.c_str(), &d_table) != SQLITE_OK)
    {
        string const errorMessage = sqlite3_errmsg(d_table);
        sqlite3_close(d_table);
        throw runtime_error("Failed to open the database: " + errorMessage);
    }
}