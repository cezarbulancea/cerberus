#include "vault.ih"

bool Vault::isInitialized() const
{
    return getVerifier().has_value();
}