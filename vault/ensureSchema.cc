#include "vault.ih"

void Vault::ensureSchema()
{                                      // Table for the encrypted entries; 
    string const sqlCommand =          // (Website, UserIdentifier) pair is unique
        "CREATE TABLE IF NOT EXISTS Vault (\n"
        "    Website        varchar(255) NOT NULL,\n"
        "    UserIdentifier varchar(255) NOT NULL,\n"
        "    nonce          blob NOT NULL,\n"
        "    tag            blob NOT NULL,\n"
        "    ciphertext     blob NOT NULL\n,"
        "    UNIQUE (Website, UserIdentifier)\n"
        ");";
                                       // Meta table for KDF salt and 
    string const sqlMeta =             // password verifier
        "CREATE TABLE IF NOT EXISTS meta (\n"
        "   Key varchar(255) PRIMARY KEY,\n"
        "   Value blob NOT NULL\n"
        ");";

    char *errmsg = nullptr;            // Execute the SQL commands
    if (sqlite3_exec(d_db, sqlCommand.c_str(), 
                     nullptr, nullptr, &errmsg) != SQLITE_OK || 
        sqlite3_exec(d_db, sqlMeta.c_str(), 
                     nullptr, nullptr, &errmsg) != SQLITE_OK)
    {
        string const errorMessage = errmsg ? errmsg : sqlite3_errmsg(d_db);
                                       // Free the error message 
        sqlite3_free(errmsg);          // allocated by SQLite 
        throw runtime_error("Schema error: " + errorMessage);
    }
}