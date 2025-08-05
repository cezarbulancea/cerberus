#include "vault.ih"
                                       // on success a session-key is derived 
void Vault::setupOrUnlock()            // and stored in d_key
{
    sqlite3_stmt *statement = nullptr; 
    bool firstRun = true;              
    string verifier;                 
                                       // check whether a verifier is already 
    char constexpr getVerifierSql[] =  // stored; if so, copy it to `verifier`
        "SELECT value FROM meta WHERE key='verifier';";

    if (sqlite3_prepare_v2(d_db, getVerifierSql, -1, &statement, nullptr) == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW)
    {                                  // copy BLOB (includes terminating NUL)
        void const *blob = sqlite3_column_blob (statement, 0);
        int size = sqlite3_column_bytes(statement, 0);
        verifier.assign(static_cast<char const *>(blob), size);

        firstRun = false;              // existing vault confirmed
    }
    sqlite3_finalize(statement);       

    if (firstRun)
    {
        cout << "No master password found - creating a new vault.\n";
                                       // prompt twice to avoid typos
        string password1 = hiddenPrompt("Create master password: ");
        string password2 = hiddenPrompt("Confirm master password: ");
        if (password1 != password2)     
            throw runtime_error("Passwords don't match. Abboring setup.");
                                               // build verifier
        char verifierBuf[crypto_pwhash_STRBYTES] = {};  
        if (crypto_pwhash_str(verifierBuf,
                              password1.c_str(), password1.size(),
                              crypto_pwhash_OPSLIMIT_MODERATE,
                              crypto_pwhash_MEMLIMIT_MODERATE) != 0)
        {
            wipeKey();                 // clear d_key if any
            throw runtime_error("Verifier generation failed");
        }
                                       // insert verifier in `meta` table
        size_t const verifierLen = strlen(verifierBuf) + 1; 
        char constexpr insertVerifierSql[] =
            "INSERT INTO meta(key,value) VALUES('verifier',?1);";

        sqlite3_prepare_v2(d_db, insertVerifierSql, -1, &statement, nullptr);
        sqlite3_bind_blob(statement, 1,
                          verifierBuf, static_cast<int>(verifierLen),
                          SQLITE_TRANSIENT);
        if (sqlite3_step(statement) != SQLITE_DONE)
        {
            wipeKey();
            string const message = sqlite3_errmsg(d_db);
            sqlite3_finalize(statement);
            throw runtime_error("Storing verifier failed: " + message);
        }
        sqlite3_finalize(statement);
                                       // derive session-key;
        deriveSessionKey(password1);   // wipes `password1` internally

        sodium_memzero(verifierBuf, sizeof verifierBuf);
        sodium_memzero(password2.data(), password2.size());

        cout << "Vault created and unlocked.\n";
        return;                                    
    }                                  // existing vault; ask for master 
                                       // password (max 3 attempts)
    for (size_t attempts = 0; attempts != 3; ++attempts)
    {
        string password = hiddenPrompt("Master password: ");
                                       // Argon2 verify — returns 0 on success
        if (crypto_pwhash_str_verify(verifier.c_str(),
                                     password.c_str(), password.size()) == 0)
        {
            deriveSessionKey(password);
            sodium_memzero(password.data(), password.size());
            cout << "Vault unlocked.\n";
            return;                                 
        }

        sodium_memzero(password.data(), password.size());
        cout << "Incorrect password.\n";
    }

    wipeKey();
    throw runtime_error("Too many failed attempts — vault remains locked.");                    
}