#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <array>
#include <cstdint>
#include <optional>
#include <vector>

#include "../key/key.hh"
#include "../dbHandle/dbHandle.hh"
#include "../secret/secret.hh"


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

        std::optional<std::string> getVerifier() const;
        bool isInitialized() const;
        void setup();
        void unlock();

        Secret add(std::string const &website, 
                   std::string const &userIdentifier, size_t length);
        std::string get(std::string const &website, 
                        std::string const &userIdentifier) const;

    private:
        void deriveSessionKey(std::string &master);
        void ensureSchema();  
        std::vector<std::uint8_t> loadOrCreateSalt();
        bool verifyMaster(std::string &password);
        void wipeKey();
};

#endif