#ifndef INCLUDED_SECRET_
#define INCLUDED_SECRET_

#include <string>

/**
 * \brief Move-only wrapper for sensitive string data with zeroization.
 *
 * Holds a secret in memory and attempts to scrub it (via `sodium_memzero`) on
 * destruction or reassignment. Copy is disabled to avoid accidental duplication
 * of sensitive data. Move operations transfer ownership.
 */
class Secret
{
    std::string d_data;

    public:
        Secret() = delete;
        explicit Secret(std::string &&secret);

        Secret(Secret const &other) = delete;
        Secret(Secret &&tmp);

        Secret &operator=(Secret const &other) = delete;
        Secret &operator=(Secret &&tmp);

        ~Secret();

        /** Read-only access to the underlying data. */
        std::string const &data() const;

    private:
        /** Best-effort zeroization followed by logical clearing. */
        void wipe();
};

#endif