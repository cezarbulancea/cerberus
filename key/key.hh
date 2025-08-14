#ifndef INCLUDED_KEY_
#define INCLUDED_KEY_

#include <array>
#include <sodium.h>


/**
 * \brief Owner of a 32-byte AEAD session key with secure zeroization.
 *
 * Provides move-only semantics, explicit validity tracking, and accessors to
 * the raw key bytes for use with libsodium. All destructive operations call
 * `sodium_memzero` to reduce the risk of key material lingering in memory.
 */
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

        /** Whether a valid key is currently stored. */
        bool valid() const;
        /** Mark the key as valid/invalid (does not change bytes). */
        void setValid(bool valid);

        /** Mutable pointer to key bytes (32 bytes). */
        unsigned char *data();
        /** Const pointer to key bytes (32 bytes). */
        unsigned char const *data() const;

        /** Size of the key in bytes. */
        size_t size() const;

    private:
        /** Securely clear key bytes and reset validity. */
        void clear();
};

#endif