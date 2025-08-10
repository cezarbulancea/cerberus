#include "vault.ih"

optional<string> Vault::getVerifier() const
{
    Statement statement;              
    string verifier;               
                                       // check whether a verifier is already 
    char constexpr getVerifierSql[] =  // stored; if so, copy it to `verifier`
        "SELECT value FROM meta WHERE key='verifier';";

    if (sqlite3_prepare_v2(d_db, getVerifierSql, -1, &statement.ptr, nullptr) 
                                    == SQLITE_OK &&
        sqlite3_step(statement.ptr) == SQLITE_ROW)
    {                                  // copy BLOB (includes terminating NUL)
        void const *blob = sqlite3_column_blob (statement.ptr, 0);
        size_t const size = sqlite3_column_bytes(statement.ptr, 0);
        verifier.assign(static_cast<char const *>(blob), size);
        return verifier;
    }
    
    return nullopt;
}