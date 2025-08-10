#include "vault.ih"

Vault::Vault(string const &filename)
:
    d_db(filename)
{          
    ensureSchema();
}