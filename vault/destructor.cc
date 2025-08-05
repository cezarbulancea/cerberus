#include "vault.ih"

Vault::~Vault()
{
    wipeKey();
}