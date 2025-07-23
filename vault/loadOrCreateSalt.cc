#include "vault.ih"

vector<uint8_t> Vault::loadOrCreateSalt()
{
    vector<uint8_t> salt{ crypto_pwhash_SALTBYTES };

    sqlite3_stmt *statement;
    string const sqlExtractSalt = "SELECT value FROM meta WHERE key='salt';";
    if (sqlite3_prepare_v2(d_table, sqlExtractSalt.c_str(), -1, &statement, nullptr)
            == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW)
    {
        auto *blob = static_cast<uint8_t const *>(sqlite3_column_blob(statement, 0));
        size_t sz = sqlite3_column_bytes(statement, 0);
        if (sz == salt.size())
            memcpy(salt.data(), blob, sz);
        sqlite3_finalize(statement);
        return salt;                   // existing salt
    }
    sqlite3_finalize(statement);
                                       // No salt yet -> create one
    randombytes_buf(salt.data(), salt.size());
    string const sqlInsertSalt = 
        "INSERT INTO meta (key,value) VALUES ('salt',?1);";
    sqlite3_prepare_v2(d_table, sqlInsertSalt.c_str(), -1, &statement, nullptr);
    sqlite3_bind_blob(statement, 1, salt.data(), salt.size(), SQLITE_TRANSIENT);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
    return salt;
}