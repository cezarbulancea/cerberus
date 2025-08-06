# Cerberus

Cerberus is a command-line password manager written in modern C++. It securely stores credentials in an encrypted SQLite database, using strong cryptography and a simple, user-friendly interface.

## Features

- **Secure storage:** Passwords are encrypted using libsodium (XChaCha20-Poly1305) and protected by a master password-derived key (Argon2id).
- **SQLite backend:** All credentials are stored in a local SQLite database.
- **Automatic password generation:** Generates strong, random passwords for new entries.
- **Simple CLI:** Add and retrieve credentials with straightforward commands.
- **Cross-platform:** Designed for Linux, but portable to other platforms with minimal changes.

## Usage

After building, run the program:

```sh
./main
```

You will be prompted to create or unlock your vault with a master password. Available commands:

- `add` — Add a new credential (website, user, password is generated automatically)
- `get` — Retrieve a password for a given website and user
- `quit` or `exit` — Exit the program

Example session:

```txt
Commands:  add   get   quit
> add
Website: example.com
User identifier: alice
Your password is: [displayed password]
✓ Stored / updated credential.
> get
Website: example.com
User identifier: alice
Password: [displayed password]
> quit
```

## Build Instructions

Requirements:

- C++26 compiler (e.g., g++ 14+)
- GNU Make
- [libsodium](https://libsodium.gitbook.io/doc/installation) development files
- [SQLite3](https://www.sqlite.org/download.html) development files

To build:

```sh
make
```

To clean build artifacts:

```sh
make clean
```

## Project Structure

- `main.cc`, `main.ih` — Main program and interface
- `cmdAdd.cc`, `cmdGet.cc` — Command handlers for adding and retrieving credentials
- `vault/` — Vault logic (encryption, database, session key management)
- `passwordGenerator/` — Password generation and verification
- `ioTools/` — Input/output utilities (including hidden password prompts)
- `dbHandle/` — SQLite database management
- `key/` — Session key management

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
