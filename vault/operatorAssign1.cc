#include "vault.ih"

Vault &Vault::operator=(Vault &&tmp) noexcept
{
    if (this != &tmp)
    {
        if (d_db)
            sqlite3_close(d_db);
        sodium_memzero(d_key.data(), d_key.size());
        d_keyValid = false;

        d_db = tmp.d_db;
        d_key = tmp.d_key;
        d_keyValid = tmp.d_keyValid;

        tmp.d_db = nullptr;
        sodium_memzero(tmp.d_key.data(), tmp.d_key.size());
        d_keyValid = false;
    }

    return *this;
}