#include "vault.ih"

Vault::~Vault()
{
    if (d_table)
        sqlite3_close(d_table);
}