#ifndef INCLUDED_PASSWORDGENERATOR_
#define INCLUDED_PASSWORDGENERATOR_

#include <sodium.h>
#include <string>

/**
 * \brief Cryptographically secure password generator.
 *
 * Generates mixed-character passwords using libsodium's CSPRNG. Guarantees
 * inclusion of at least one character from each class (lower/upper/digit/symbol)
 * when length >= 4, then fills the remainder from the full alphabet and
 * shuffles with a Fisher–Yates permutation driven by `randombytes_uniform`.
 */
class PasswordGenerator
{
    public:
        PasswordGenerator() = default;

        /**
         * Generate a password of exactly `length` characters.
         * \throws std::invalid_argument if `length < 4`.
         */
        std::string generatePassword(size_t length) const;

    private:             
        /**
         * Pick one uniformly from a NUL-terminated C-string constant.
         *
         * We sample from [0, N-2] to exclude the trailing '\0'.
         */             
        template <size_t N>
        static char pickOne(char const (&set)[N]);
};

#include "pickOne.i"

#endif