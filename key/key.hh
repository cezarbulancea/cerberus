#ifndef INCLUDED_KEY_
#define INCLUDED_KEY_

#include <array>
#include <sodium.h>

class Key
{
    std::array<uint8_t, crypto_aead_xchacha20poly1305_ietf_KEYBYTES> d_data{};
    bool d_valid = false;

    public:
        Key() = default;

        Key(Key const &other) = delete;
        Key(Key &&tmp);

        Key &operator=(Key const &other) = delete;
        Key &operator=(Key &&tmp);

        ~Key();

        bool valid() const;
        void setValid(bool valid);

        unsigned char *data();
        unsigned char const *data() const;

        size_t size() const;

    private:
        void clear();
};

#endif