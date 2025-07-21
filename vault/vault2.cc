#include "vault.ih"

Vault::Vault(Vault &&tmp)
:
    d_table(tmp.d_table)
{
    tmp.d_table = nullptr;
}