#include "secret.ih"

Secret::Secret(string const &secret)
:
    d_data(move(secret))
{}