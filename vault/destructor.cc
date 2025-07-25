#include "vault.ih"

Vault::~Vault()
{
    wipeKey();
    if (d_db)
        sqlite3_close(d_db);
}