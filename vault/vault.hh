#ifndef INCLUDED_VAULT_
#define INCLUDED_VAULT_

#include <array>
#include <cstdint>
#include <optional>
#include <vector>

#include "../key/key.hh"
#include "../dbHandle/dbHandle.hh"
#include "../secret/secret.hh"

/**
 * \brief Persistent secrets container backed by SQLite with AEAD encryption.
 *
 * This class is responsible for:
 * 
 *  - Creating and maintaining the SQLite schema (a `Vault` table for entries
 *    and a `meta` table for KDF salt + password verifier).
 * 
 *  - Deriving a per-session encryption key from the *master password* using
 *    libsodium's Argon2id (crypto_pwhash) and a stored random salt.
 * 
 *  - Encrypting newly generated passwords with XChaCha20-Poly1305 (IETF) and
 *    authenticated associated data (AAD) set to `website + '\0' + userIdentifier`.
 * 
 *  - Decrypting stored entries after the vault is unlocked.
 * 
 *  - Zeroizing sensitive material in memory where feasible.
 */
class Vault
{
    DbHandle d_db;                     // RAII handle for the sqlite db connection
    Key      d_key;                    // 32 bytes session key 

    public:
        Vault(std::string const &filename = "vault.db");

        Vault(Vault const &other) = delete;
        Vault(Vault &&tmp)        = delete;

        Vault &operator=(Vault const &other) = delete;
        Vault &operator=(Vault &&tmp)        = delete;

        ~Vault() = default;
        
        /** Return the password verifier (if any) from the meta table.*/
        std::optional<std::string> getVerifier() const;

        /** True if the vault has been initialized (`verifier` present).*/                                      
        bool isInitialized() const;    

        /** First-time setup: prompt for master password, store verifier, 
         *  derive session key.*/
        void setup();

        /** Prompt for master password (up to MAX_ATTEMPTS) and derive session key.*/
        void unlock();

        /**
         * Insert or replace an entry for (website, userIdentifier).
         * Generates a random password of `length`, encrypts it using the current
         * session key and returns it wrapped in `Secret`.
         * \throws std::runtime_error if the vault is locked or on DB/crypto error.
         */
        Secret add(std::string const &website, 
                   std::string const &userIdentifier, size_t length);

        /**
         * Retrieve and decrypt the password for (website, userIdentifier).
         * \throws std::runtime_error if the vault is locked, record is missing,
         *         or authentication fails.
         */
        std::string get(std::string const &website, 
                        std::string const &userIdentifier) const;

    private:
        /** Derive a 32-byte session key with Argon2id from the provided 
         *  master password.*/
        void deriveSessionKey(std::string &master);

        /** Ensure the required tables exist.*/
        void ensureSchema();

        /** Load the stored Argon2 salt or create and persist a new one. */
        std::vector<std::uint8_t> loadOrCreateSalt();

        /** Verify the provided master password against the stored verifier;
         *  derive session key on success.*/
        bool verifyMaster(std::string &password);

        /** Zeroize session key and mark it invalid.*/
        void wipeKey();
};

#endif