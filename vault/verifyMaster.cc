#include "vault.ih"

bool Vault::verifyMaster(string &password)
{
    auto verifier = getVerifier();
    if (!verifier)
        return false;

    if (crypto_pwhash_str_verify(verifier->c_str(),
                                 password.c_str(), password.size()) == 0)
    {
        deriveSessionKey(password);
        cout << "Vault unlocked.\n";
        return true;                                 
    }

    sodium_memzero(password.data(), password.size());
    cout << "Incorrect password.\n";
    return false;
}