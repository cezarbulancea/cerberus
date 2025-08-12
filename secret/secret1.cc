#include "secret.ih"

Secret::Secret(string &&secret)
:
    d_data(move(secret))
{}