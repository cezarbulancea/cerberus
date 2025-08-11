#include "secret.ih"

void Secret::wipe()
{
    if (!d_data.empty()) 
    {
        sodium_memzero(d_data.data(), d_data.size());
        d_data.clear();
    }
}