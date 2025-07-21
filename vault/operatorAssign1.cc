#include "vault.ih"

Vault &Vault::operator=(Vault &&tmp)
{
    if (this != &tmp)
    {
        if (d_table)
            sqlite3_close(d_table);

        d_table = tmp.d_table;
        tmp.d_table = nullptr;
    }

    return *this;
}