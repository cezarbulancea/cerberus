#ifndef INCLUDED_SECRET_
#define INCLUDED_SECRET_

#include <string>

class Secret
{
    std::string d_data;

    public:
        Secret(std::string const &secret);

        Secret(Secret const &other) = delete;
        Secret(Secret &&tmp);

        Secret &operator=(Secret const &other) = delete;
        Secret &operator=(Secret &&tmp);

        ~Secret();

        std::string const &data() const;

    private:
        void wipe();
};

#endif