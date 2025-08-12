template <size_t N>
char PasswordGenerator::pickOne(char const (&set)[N])
{
    return set[randombytes_uniform(static_cast<uint32_t>(N - 1))];
}