#include "key.ih"

Key::Key(Key &&tmp)
:
    d_data(tmp.d_data),
    d_valid(tmp.d_valid)
{
    tmp.clear();
}