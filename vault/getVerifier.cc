#include "vault.ih"

optional<string> Vault::getVerifier() const
{
    sqlite3_stmt *statement = nullptr;              
    string verifier;
    bool verifierExists = false;                 
                                       // check whether a verifier is already 
    char constexpr getVerifierSql[] =  // stored; if so, copy it to `verifier`
        "SELECT value FROM meta WHERE key='verifier';";

    if (sqlite3_prepare_v2(d_db, getVerifierSql, -1, &statement, nullptr) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW)
    {                                  // copy BLOB (includes terminating NUL)
        void const *blob = sqlite3_column_blob (statement, 0);
        size_t const size = sqlite3_column_bytes(statement, 0);
        verifier.assign(static_cast<char const *>(blob), size);
        verifierExists = true;
    }
    sqlite3_finalize(statement);

    if (verifierExists)
        return verifier;
    
    return nullopt;
}