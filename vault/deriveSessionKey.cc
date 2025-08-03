#include "vault.ih"

void Vault::deriveSessionKey(string const &master)
{                                      // fetch or create a random salt 
                                       // (16 bytes) stored in meta table
    vector<uint8_t> salt = loadOrCreateSalt();
                                       
                                       // derive a 32-byte key with argon2-id
    if (crypto_pwhash(d_key.data(), d_key.size(),
                      master.data(), master.size(),
                      salt.data(),
                      crypto_pwhash_OPSLIMIT_MODERATE,
                      crypto_pwhash_MEMLIMIT_MODERATE,
                      crypto_pwhash_ALG_DEFAULT) != 0)
        throw runtime_error("Key derivation failed");
    
    d_keyValid = true;                 // mark vault unlocked 
    sodium_memzero(const_cast<char *>(master.data()), master.size());
}