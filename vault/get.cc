#include "vault.ih"

string Vault::get(string const &website, string const &userIdentifier) const
{
    if (!d_key.valid)
        throw runtime_error("The vault is locked. If you want to fetch a "
                            "password, you have to unlock it first.");

    sqlite3_stmt *statement = nullptr;
    string const fetchPassSql =        // pull record
        "SELECT nonce, tag, ciphertext "
        "FROM   Vault "
        "WHERE  Website=?1 AND UserIdentifier=?2;";

    if (sqlite3_prepare_v2(d_db, fetchPassSql.c_str(), -1,
                           &statement, nullptr) != SQLITE_OK)
        throw runtime_error("SQLite prepare failed: " + string(sqlite3_errmsg(d_db)));

    sqlite3_bind_text(statement, 1, website.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, userIdentifier.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(statement) != SQLITE_ROW)
    {
        sqlite3_finalize(statement);
        throw runtime_error("No password stored for “" + website
                               + "” / user “" + userIdentifier + "”.");
    }

    auto blob = [&](int col) {         // extract nonce, tag and cipher
        auto ptr = static_cast<unsigned char const *>(sqlite3_column_blob(statement, col));
        int size = sqlite3_column_bytes(statement, col);
        return vector<uint8_t>(ptr, ptr + size);
    };

    vector<uint8_t> nonce = blob(0);
    vector<uint8_t> tag   = blob(1);
    vector<uint8_t> cipher= blob(2);
                                       // re-attach tag
    cipher.insert(cipher.end(), tag.begin(), tag.end());   

    sqlite3_finalize(statement);       
                                       // decrypt
    vector<uint8_t> plain(cipher.size());          
    unsigned long long plainLength = 0;

    if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            plain.data(), &plainLength,
            /*nsec=*/nullptr,
            cipher.data(), cipher.size(),
            /*ad=*/nullptr, 0,
            nonce.data(),
            d_key.data.data()) != 0)
        throw runtime_error("Decryption failed (tampering or wrong key)");

    plain.resize(plainLength);
    string const password(reinterpret_cast<char *>(plain.data()), plain.size());

    sodium_memzero(plain.data(), plain.size());
    sodium_memzero(cipher.data(), cipher.size());

    return password;
}