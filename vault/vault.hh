#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <array>
#include <cstdint>
#include <cstring>
#include <sodium.h>
#include <stdio.h>
#include <vector>

#include "../dbHandle/dbHandle.hh"


class Vault
{
    DbHandle d_db;
    std::array<std::uint8_t, crypto_aead_xchacha20poly1305_IETF_KEYBYTES> d_key;
    bool d_keyValid = false;

    public:
        Vault(std::string const &filename = "vault.db");

        Vault(Vault const &other) = delete;
        Vault(Vault &&tmp)        = delete;

        Vault &operator=(Vault const &other) = delete;
        Vault &operator=(Vault &&tmp)        = delete;

        ~Vault();

        void add(std::string const &website, 
                 std::string const &userIdentifier, size_t length);
        std::string get(std::string const &website, 
                        std::string const &userIdentifier) const;

        std::string hiddenPrompt(std::string const &prompt);

    private:
        void ensureSchema();
        void deriveSessionKey(std::string const &master);      
        std::vector<std::uint8_t> loadOrCreateSalt();
                                       // setup a new vault or 
        void setupOrUnlock();          // unlock an existent one
        void wipeKey();
};

#endif