#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <array>
#include <cstdint>
#include <cstring>
#include <sodium.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <vector>


class Vault
{
    sqlite3 *d_table;
    std::array<std::uint8_t, crypto_aead_xchacha20poly1305_IETF_KEYBYTES> d_key;
    bool d_keyValid = false;

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

    private:
        void openDatabase(std::string const &filename);
        void ensureSchema();
        void deriveSessionKey();       // Argon2-id
        std::vector<std::uint8_t> loadOrCreateSalt();
        std::string hiddenPrompt(std::string const &prompt);
        
        void wipeKey();
};

#endif