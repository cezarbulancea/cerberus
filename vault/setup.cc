#include "vault.ih"

void Vault::setup()
{   
    Statement statement;
                                       // prompt twice to avoid typos
    string password1 = IOTools::hiddenPrompt("Create master password: ");
    string password2 = IOTools::hiddenPrompt("Confirm master password: ");
    if (password1 != password2)     
        throw runtime_error("Passwords don't match. Aborting setup.");
                                       // build verifier
    char verifierBuf[crypto_pwhash_STRBYTES] = {};  
    if (crypto_pwhash_str(verifierBuf,
                            password1.c_str(), password1.size(),
                            crypto_pwhash_OPSLIMIT_MODERATE,
                            crypto_pwhash_MEMLIMIT_MODERATE) != 0)
        throw runtime_error("Verifier generation failed");
                                       // insert verifier in `meta` table
    size_t const verifierLen = strlen(verifierBuf) + 1; 
    char constexpr insertVerifierSql[] =
        "INSERT INTO meta(key,value) VALUES('verifier',?1);";

    if (sqlite3_prepare_v2(d_db, insertVerifierSql, -1,
                           &statement.ptr, nullptr) != SQLITE_OK)
        throw runtime_error("SQLite prepare failed: " + string(sqlite3_errmsg(d_db)));
    sqlite3_bind_blob(statement.ptr, 1,
                      verifierBuf, static_cast<int>(verifierLen),
                      SQLITE_TRANSIENT);
    if (sqlite3_step(statement.ptr) != SQLITE_DONE)
    {
        string const message = sqlite3_errmsg(d_db);
        throw runtime_error("Storing verifier failed: " + message);
    }
                                       // derive session-key;
    deriveSessionKey(password1);       // wipes `password1` internally

    sodium_memzero(verifierBuf, sizeof verifierBuf);
    sodium_memzero(password2.data(), password2.size());

    cout << "Vault created and unlocked.\n";
    return;
}