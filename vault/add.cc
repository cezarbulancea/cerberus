#include "vault.ih"

void Vault::add(string const &website, string const &userIdentifier,
                size_t length)
{
    if (!d_key.valid)
        throw runtime_error("The vault is locked. If you want to add an entry, "
                            "you have to unlock it first.");

    PasswordGenerator generator;       // generate a password of the given length
    string const password = generator.generatePassword(length);

    cout << "Your password is: " << password << '\n';

    vector<uint8_t> nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
                                       // 24-byte random nonce
    randombytes_buf(nonce.data(), nonce.size());    
                                       // cipher = password + 16-byte tag
    vector<uint8_t> cipher(password.size() 
                           + crypto_aead_xchacha20poly1305_ietf_ABYTES);

    unsigned long long cipherLength = 0;
    crypto_aead_xchacha20poly1305_ietf_encrypt(
        cipher.data(), &cipherLength,
        reinterpret_cast<unsigned char const *>(password.data()),
        password.size(),
        /*ad=*/nullptr, 0,
        /*nsec=*/nullptr,
        nonce.data(),
        d_key.data.data()
    );
                                       // split tag from ciphertext for storage
    size_t tagLength = crypto_aead_xchacha20poly1305_ietf_ABYTES;
    vector<uint8_t> tag(cipher.end() - tagLength, cipher.end());
    cipher.resize(cipher.size() - tagLength);

    Statement statement;
    string const addValuesSql = 
        "INSERT INTO Vault (Website, UserIdentifier, nonce, tag, ciphertext) "
        "VALUES (?1, ?2, ?3, ?4, ?5) "
        "ON CONFLICT(Website, UserIdentifier) DO UPDATE SET "
        "  nonce=excluded.nonce, "
        "  tag=excluded.tag, "
        "  ciphertext=excluded.ciphertext;";

    if (sqlite3_prepare_v2(d_db, addValuesSql.c_str(), 
                           -1, &statement.ptr, nullptr) != SQLITE_OK)
        throw runtime_error("SQLite prepare failed: " + string(sqlite3_errmsg(d_db)));

    sqlite3_bind_text (statement.ptr, 1, website.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text (statement.ptr, 2, userIdentifier.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_blob (statement.ptr, 3, nonce.data(), nonce.size(), SQLITE_TRANSIENT);
    sqlite3_bind_blob (statement.ptr, 4, tag.data(), tag.size(), SQLITE_TRANSIENT);
    sqlite3_bind_blob (statement.ptr, 5, cipher.data(), cipher.size(), SQLITE_TRANSIENT);

    if (sqlite3_step(statement.ptr) != SQLITE_DONE)
    {
        string const message = sqlite3_errmsg(d_db);
        throw runtime_error("SQLite insert failed: " + message);
    }

    sodium_memzero(const_cast<char *>(password.data()), password.size());
    sodium_memzero(cipher.data(), cipher.size());
    sodium_memzero(tag.data(), tag.size());
}