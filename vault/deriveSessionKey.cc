#include "vault.ih"

void Vault::deriveSessionKey()
{                                      // Fetch or create a random salt 
                                       // (16 bytes) stored in meta table
    vector<uint8_t> salt = loadOrCreateSalt();
                                       // Ask user for master password
    string master = hiddenPrompt("Master password: ");

    if (crypto_pwhash(d_key.data(), d_key.size(),
                      master.data(), master.size(),
                      salt.data(),
                      crypto_pwhash_OPSLIMIT_MODERATE,
                      crypto_pwhash_MEMLIMIT_MODERATE,
                      crypto_pwhash_ALG_DEFAULT) != 0)
        throw runtime_error("Key derivation failed");
                                       // hygiene
    sodium_memzero(master.data(), master.size());
}