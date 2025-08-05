#include "vault.ih"

void Vault::wipeKey()
{
    sodium_memzero(d_key.data(), d_key.size());
    d_keyValid = false;
}
