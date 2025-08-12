#include "key.ih"

void Key::clear()
{
    sodium_memzero(d_data.data(), d_data.size());
    d_valid = false;
}