#include "vault.ih"

vector<uint8_t> Vault::loadOrCreateSalt()
{
    vector<uint8_t> salt(crypto_pwhash_SALTBYTES);

    {
        Statement statement;
        char constexpr sqlExtractSalt[] = 
            "SELECT value FROM meta WHERE key='salt';";
        if (sqlite3_prepare_v2(d_db, sqlExtractSalt, -1, &statement.ptr, nullptr)
                == SQLITE_OK &&
            sqlite3_step(statement.ptr) == SQLITE_ROW)
        {
            uint8_t const *blob = static_cast<uint8_t const *>(
                                            sqlite3_column_blob(statement.ptr, 0));
            size_t numberBytes = sqlite3_column_bytes(statement.ptr, 0);
            if (numberBytes != salt.size())
                throw runtime_error("Invalid salt size in DB");
            memcpy(salt.data(), blob, numberBytes);
            return salt;               // existing salt
        }
    }                                  
                                       // No salt yet -> create one
    randombytes_buf(salt.data(), salt.size());

    {
        Statement statement;
        char constexpr sqlInsertSalt[] = 
            "INSERT INTO meta (key, value) VALUES ('salt',?1);";
        if (sqlite3_prepare_v2(d_db, sqlInsertSalt, -1, &statement.ptr, nullptr) != SQLITE_OK)
            throw runtime_error("SQLite prepare failed: " 
                                + string(sqlite3_errmsg(d_db)));
        sqlite3_bind_blob(statement.ptr, 1, salt.data(), salt.size(), SQLITE_TRANSIENT);
        if (sqlite3_step(statement.ptr) != SQLITE_DONE)
            throw runtime_error("SQLite insert failed: " 
                                + string(sqlite3_errmsg(d_db)));
    }
    
    return salt;
}