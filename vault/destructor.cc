#include "vault.ih"

Vault::~Vault()
{
    wipeKey();
    if (d_table)
        sqlite3_close(d_table);
}