#include "vault.ih"

namespace
{
    enum
    {
        MAX_ATTEMPTS = 3
    };
}

void Vault::unlock()
{                                      // ask for master password
    for (size_t attempts = 0; attempts != MAX_ATTEMPTS; ++attempts)
    {
        string password = IOTools::hiddenPrompt("Master password: ");
                                       // Argon2 verify — returns 0 on success
        if (verifyMaster(password))
            return;
    }

    wipeKey();
    throw runtime_error("Too many failed attempts — vault remains locked.");
}