#include "vault.ih"

Vault::Vault(string const &filename)
:
    d_db(nullptr)
{
    if (sodium_init() < 0)
        throw runtime_error("libsodium init failed");

    openDatabase(filename);          
    ensureSchema();
    setupOrUnlock();
}