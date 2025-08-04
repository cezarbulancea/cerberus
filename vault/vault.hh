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
    sqlite3 *d_db;
    std::array<std::uint8_t, crypto_aead_xchacha20poly1305_IETF_KEYBYTES> d_key;
    bool d_keyValid = false;

    public:
        Vault(std::string const &filename = "vault.db");

        Vault(Vault const &other) = delete;
        Vault(Vault &&tmp);

        Vault &operator=(Vault const &other) = delete;
        Vault &operator=(Vault &&tmp);

        ~Vault();

        void add(std::string const &website, 
                 std::string const &userIdentifier, size_t length);
        std::string get(std::string const &website, 
                        std::string const &userIdentifier) const;
        bool erase(std::string const &website, std::string const &userIdentifier);
        void list();

        std::string hiddenPrompt(std::string const &prompt);

    private:
        void openDatabase(std::string const &filename);
        void ensureSchema();
        void deriveSessionKey(std::string const &master);      
        std::vector<std::uint8_t> loadOrCreateSalt();
                                       // setup a new vault or 
        void setupOrUnlock();          // unlock an existent one
        void wipeKey();
};

#endif