#include "key.ih"

Key &Key::operator=(Key &&tmp)
{
    if (this != &tmp) 
    {
        clear();

        d_data = tmp.d_data;
        d_valid = tmp.d_valid;

        tmp.clear();
    }

    return *this;
}