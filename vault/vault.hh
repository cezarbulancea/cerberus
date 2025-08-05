#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <array>
#include <cstdint>
#include <sodium.h>
#include <vector>

#include "../dbHandle/dbHandle.hh"
#include "../key/key.hh"


class Vault
{
    DbHandle d_db;
    Key      d_key;

    public:
        Vault(std::string const &filename = "vault.db");

        Vault(Vault const &other) = delete;
        Vault(Vault &&tmp)        = delete;

        Vault &operator=(Vault const &other) = delete;
        Vault &operator=(Vault &&tmp)        = delete;

        ~Vault() = default;

        void add(std::string const &website, 
                 std::string const &userIdentifier, size_t length);
        std::string get(std::string const &website, 
                        std::string const &userIdentifier) const;

    private:
        void ensureSchema();
        void deriveSessionKey(std::string const &master);      
        std::vector<std::uint8_t> loadOrCreateSalt();
                                       // setup a new vault or 
        void setupOrUnlock();          // unlock an existent one
        void wipeKey();
};

#endif