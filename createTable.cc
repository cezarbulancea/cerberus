#include "main.ih"

bool createTable()
{
    sqlite3 *table;
                                       // Open (or create) the database
    if (sqlite3_open("vault.db", &table) != SQLITE_OK)
    {
        cerr << "Failed to open the database: " 
             << sqlite3_errmsg(table) << '\n';
        sqlite3_close(table);
        return 1;
    }

    string sqlCommand =                // SQL command to create the table
        "CREATE TABLE IF NOT EXISTS Vault (\n"
        "    Website varchar(255),\n"
        "    UserIdentifier varchar(255),\n"
        "    Password varchar(255)\n"
        ");";

    char *errmsg = 0;                  // Execute the SQL command
    int returnCode = sqlite3_exec(table, sqlCommand.c_str(), 0, 0, &errmsg);

    if (returnCode != SQLITE_OK)
    {
        cerr << "Failed to create the database: " 
             << (errmsg ? errmsg : sqlite3_errmsg(table)) << '\n';
                                       // Free the error message 
        sqlite3_free(errmsg);          // allocated by SQLite 
        sqlite3_close(table);
        return 1;
    }

    if (sqlite3_close(table) != SQLITE_OK)
    {
        cerr << "Failed to close database: " 
             << sqlite3_errmsg(table) << '\n';
        return 1;
    }

    return 0;
}