#include "key.ih"

Key::~Key()
{
    sodium_memzero(data.data(), data.size());
    valid = false;
}