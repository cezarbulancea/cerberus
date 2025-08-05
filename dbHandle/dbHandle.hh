#ifndef INCLUDED_DBHANDLE_
#define INCLUDED_DBHANDLE_

#include <sqlite3.h>
#include <string>

class DbHandle
{
    sqlite3 *d_db = nullptr;

    public:
        DbHandle(std::string const &filename = "vault.db");

        DbHandle(DbHandle const &other) = delete;
        DbHandle(DbHandle &&tmp) noexcept;

        DbHandle &operator=(DbHandle const &other) = delete;
        DbHandle &operator=(DbHandle &&tmp) noexcept;

        ~DbHandle();

        operator sqlite3*() const noexcept;
};

#endif