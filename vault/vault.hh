#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <sqlite3.h>
#include <stdio.h>
#include <string>

class Vault
{
    sqlite3 *d_table;

    public:
        Vault(std::string const &filename = "vault.db");

        Vault(Vault const &other) = delete;
        Vault(Vault &&tmp);

        Vault &operator=(Vault const &other) = delete;
        Vault &operator=(Vault &&tmp);

        ~Vault();

        bool add(std::string const &website, 
                 std::string const &userIdentifier, size_t length);
        bool get(std::string const &website, std::string const &userIdentifier);
        bool erase(std::string const &website, std::string const &userIdentifier);
        void list();
};

#endif