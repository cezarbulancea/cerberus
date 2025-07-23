#include "vault.ih"

void Vault::ensureSchema()
{
    string const sqlCommand =          // SQL command to create the table
        "CREATE TABLE IF NOT EXISTS Vault (\n"
        "    Website        varchar(255) NOT NULL,\n"
        "    UserIdentifier varchar(255) NOT NULL,\n"
        "    nonce          blob NOT NULL,\n"
        "    tag            blob NOT NULL,\n"
        "    ciphertext     blob NOT NULL\n,"
        "    UNIQUE (Website, UserIdentifier)\n"
        ");";

    string const sqlMeta = 
        "CREATE TABLE IF NOT EXISTS meta (\n"
        "   Key varchar(255) PRIMARY KEY,\n"
        "   Value blob NOT NULL\n"
        ");";

    char *errmsg = nullptr;            // Execute the SQL commands
    if (sqlite3_exec(d_table, sqlCommand.c_str(), 
                     nullptr, nullptr, &errmsg) != SQLITE_OK || 
        sqlite3_exec(d_table, sqlMeta.c_str(), 
                    nullptr, nullptr, &errmsg) != SQLITE_OK)
    {
        string const errorMessage = errmsg ? errmsg : sqlite3_errmsg(d_table);
                                       // Free the error message 
        sqlite3_free(errmsg);          // allocated by SQLite 
        throw runtime_error("Schema error: " + errorMessage);
    }
}