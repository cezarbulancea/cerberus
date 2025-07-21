#include "vault.ih"

Vault::Vault(string const &filename)
:
    d_table(nullptr)
{                                      // Open (or create) the database
    if (sqlite3_open(filename.c_str(), &d_table) != SQLITE_OK)
    {
        string const errorMessage = sqlite3_errmsg(d_table);
        sqlite3_close(d_table);
        throw runtime_error("Failed to open the database: " + errorMessage);
    }

    string const sqlCommand =          // SQL command to create the table
        "CREATE TABLE IF NOT EXISTS Vault (\n"
        "    Website        varchar(255),\n"
        "    UserIdentifier varchar(255),\n"
        "    Password       varchar(255)\n"
        ");";

    char *errmsg = nullptr;            // Execute the SQL command
    int returnCode = sqlite3_exec(d_table, sqlCommand.c_str(), 
                                  nullptr, nullptr, &errmsg);
    if (returnCode != SQLITE_OK)
    {
        string const errorMessage = errmsg ? errmsg : sqlite3_errmsg(d_table);
                                       // Free the error message 
        sqlite3_free(errmsg);          // allocated by SQLite 
        sqlite3_close(d_table);
        throw runtime_error("Failed to create table: " + errorMessage);
    }
}