#include "vault.ih"

bool Vault::add(string const &website, string const &userIdentifier, size_t length)
{                                      // Open (or create) the database
    if (sqlite3_open("vault.db", &d_db) != SQLITE_OK)
    {
        cerr << "Failed to open the database: " 
             << sqlite3_errmsg(d_db) << '\n';
        sqlite3_close(d_db);
        return 1;
    }

    PasswordGenerator generator;       // Generate a password of the given length
    string password = generator.generatePassword(length);
                                       // Prepare an INSERT statement
    string sqlCommand =                // with 3 placeholders
        "INSERT INTO Vault (Website, UserIdentifier, Password)\n"
        "VALUES (?, ?, ?);";

    sqlite3_stmt *stmt = nullptr;
    int returnCode = sqlite3_prepare_v2(d_db, sqlCommand.c_str(), -1, &stmt, nullptr);

    if (returnCode != SQLITE_OK) 
    {
        cerr << "Failed to prepare statement: " 
             << sqlite3_errmsg(d_db) << "\n";
        sqlite3_close(d_db);
        return 1;
    }                                
                                       // Bind the values into the 3 slots 
    sqlite3_bind_text(stmt, 1, website.c_str(),        -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, userIdentifier.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, password.c_str(),       -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) 
    {
        cerr << "Execution failed: " 
             << sqlite3_errmsg(d_db) << "\n";
        sqlite3_finalize(stmt);
        sqlite3_close(d_db);
        return 1;
    }

    sqlite3_finalize(stmt);            // Clean up the prepared statement
    cout << "Password stored successfully!\n";

    if (sqlite3_close(d_db) != SQLITE_OK)
    {
        cerr << "Failed to close database: " 
             << sqlite3_errmsg(d_db) << '\n';
        return 1;
    }

    return 0;
}