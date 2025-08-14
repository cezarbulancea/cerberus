#ifndef INCLUDED_DBHANDLE_
#define INCLUDED_DBHANDLE_

#include <sqlite3.h>
#include <string>

/**
 * \brief RAII wrapper around a `sqlite3*` connection.
 *
 * Opens the database in the constructor (creating it if needed) and closes the
 * connection in the destructor. Copy is disabled; move transfers ownership of
 * the raw handle. Implicit conversion to `sqlite3*` is provided for use with
 * the SQLite C API.
 */
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