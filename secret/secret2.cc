#include "secret.ih"

Secret::Secret(Secret &&tmp)
:
    d_data(move(tmp.d_data))
{}