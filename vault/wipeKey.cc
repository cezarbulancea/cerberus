#include "vault.ih"

void Vault::wipeKey()
{
    if (d_keyValid) 
    {
        sodium_memzero(d_key.data(), d_key.size());
        d_keyValid = false;
    }
}
