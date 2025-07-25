#include "vault.ih"

Vault &Vault::operator=(Vault &&tmp)
{
    if (this != &tmp)
    {
        if (d_db)
            sqlite3_close(d_db);

        d_db = tmp.d_db;
        tmp.d_db = nullptr;
    }

    return *this;
}