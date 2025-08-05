#include "vault.ih"

void Vault::wipeKey()
{
    sodium_memzero(d_key.data.data(), d_key.data.size());
    d_key.valid= false;
}