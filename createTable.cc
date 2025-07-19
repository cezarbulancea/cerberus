#include "main.ih"

bool createTable()
{
    sqlite3 *table;
                                       // Open the database
    int openingFlag = sqlite3_open("vault.db", &table);

    if (openingFlag != SQLITE_OK)
    {
        cerr << "Failed to open the database: " << sqlite3_errmsg(table) << '\n';
        return 1;
    }

    string sqlCommand = 
        "CREATE TABLE IF NOT EXISTS Vault (\n"
        "    Website varchar(255),\n"
        "    UserIdentifier varchar(255),\n"
        "    Password varchar(255)\n"
        ");";

    char *errmsg = 0;
    int executionFlag = sqlite3_exec(table, sqlCommand.c_str(), 0, 0, &errmsg);

    if (executionFlag != SQLITE_OK)
    {
        cerr << "Failed to create the database: " << sqlite3_errmsg(table) << '\n';
        return 1;
    }

    int closingFlag = sqlite3_close(table);

    if (closingFlag != SQLITE_OK)
    {
        cerr << "Failed to close database: " << sqlite3_errmsg(table) << '\n';
        return 1;
    }

    return 0;
}