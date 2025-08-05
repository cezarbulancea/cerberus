#ifndef INCLUDED_KEY_
#define INCLUDED_KEY_

#include <array>
#include <sodium.h>

struct Key
{
    std::array<uint8_t, crypto_aead_xchacha20poly1305_ietf_KEYBYTES> data{};
    bool valid = false;

    ~Key();
};

#endif