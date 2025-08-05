#include "vault.ih"

Vault::Vault(Vault &&tmp) noexcept
:
    d_db(tmp.d_db),
    d_key(tmp.d_key),
    d_keyValid(tmp.d_keyValid)
{
    tmp.d_db = nullptr;
    sodium_memzero(tmp.d_key.data(), tmp.d_key.size());
    tmp.d_keyValid = false;
}