#include "vault.ih"

Vault::Vault(Vault &&tmp)
:
    d_db(tmp.d_db)
{
    tmp.d_db = nullptr;
}