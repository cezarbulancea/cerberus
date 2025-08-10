#include "vault.ih"

vector<uint8_t> Vault::loadOrCreateSalt()
{
    vector<uint8_t> salt(crypto_pwhash_SALTBYTES);

    sqlite3_stmt *statement = nullptr;
    string const sqlExtractSalt = "SELECT value FROM meta WHERE key='salt';";
    if (sqlite3_prepare_v2(d_db, sqlExtractSalt.c_str(), -1, &statement, nullptr)
            == SQLITE_OK &&
        sqlite3_step(statement) == SQLITE_ROW)
    {
        uint8_t const *blob = static_cast<uint8_t const *>(
                                            sqlite3_column_blob(statement, 0));
        size_t numberBytes = sqlite3_column_bytes(statement, 0);
        if (numberBytes != salt.size())
        {
            sqlite3_finalize(statement);
            throw runtime_error("Invalid salt size in DB");
        }
        memcpy(salt.data(), blob, numberBytes);
        sqlite3_finalize(statement);
        return salt;                   // existing salt
    }
    sqlite3_finalize(statement);
                                       // No salt yet -> create one
    randombytes_buf(salt.data(), salt.size());
    string const sqlInsertSalt = 
        "INSERT INTO meta (key, value) VALUES ('salt',?1);";
    sqlite3_prepare_v2(d_db, sqlInsertSalt.c_str(), -1, &statement, nullptr);
    sqlite3_bind_blob(statement, 1, salt.data(), salt.size(), SQLITE_TRANSIENT);
    sqlite3_step(statement);

    sqlite3_finalize(statement);

    return salt;
}