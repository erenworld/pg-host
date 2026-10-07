hostname 1.0.2
==============

This library contains a single PostgreSQL extension, `hostname`, which
provides a function, `hostname()`, that returns the database server's host
name:

    % SELECT hostname();
     hostname 
    ----------
     myserver

Requirements
------------
* PostgreSQL 18 or later
* A C compiler and make (GNU make on Linux, the macOS `make` is usually enough)
* PostgreSQL development files (`pg_config` and the server headers)

### macOS (Homebrew)

    xcode-select --install
    brew install postgresql@18

Homebrew ships the server headers and `pg_config` with the formula, so no
separate development package is needed. Since `postgresql@18` is keg-only,
add it to your PATH:

    echo 'export PATH="/opt/homebrew/opt/postgresql@18/bin:$PATH"' >> ~/.zshrc
    source ~/.zshrc

(On Intel Macs, replace `/opt/homebrew` with `/usr/local`.)

### Debian / Ubuntu (apt)

    sudo apt install build-essential postgresql-18 postgresql-server-dev-18

Installation
------------
To build and install hostname, just do this:

    make
    make installcheck
    make install

On Debian/Ubuntu, `make install` needs root:

    sudo make install

On macOS with Homebrew, `sudo` is not needed, since Homebrew installs into a
directory you own.

If you encounter an error such as:

    "Makefile", line 8: Need an operator

You need to use GNU make, which may well be installed on your system as
`gmake` (on macOS: `brew install make`):

    gmake
    gmake installcheck
    gmake install

If you encounter an error such as:

    make: pg_config: Command not found

Be sure that you have `pg_config` installed and in your path. On macOS, see
the PATH step above. On Debian/Ubuntu, be sure that
`postgresql-server-dev-18` is installed. If necessary, tell the build process
where to find it:

    make PG_CONFIG=/path/to/pg_config
    make installcheck PG_CONFIG=/path/to/pg_config
    sudo make install PG_CONFIG=/path/to/pg_config

Typical paths:

    macOS (Homebrew):  /opt/homebrew/opt/postgresql@18/bin/pg_config
    Debian/Ubuntu:     /usr/lib/postgresql/18/bin/pg_config

If you encounter an error such as:

    ERROR:  must be owner of database regression

You need to run the test suite using a super user:

    # Debian/Ubuntu: the default "postgres" super user
    make installcheck PGUSER=postgres

    # macOS (Homebrew): your macOS username
    make installcheck PGUSER=$(whoami)

Usage
-----
Make sure PostgreSQL is running:

    # macOS
    brew services start postgresql@18

    # Debian/Ubuntu
    sudo systemctl start postgresql

Then connect to a database as a super user and run:

    CREATE EXTENSION hostname;

To install it into a specific schema:

    CREATE EXTENSION hostname SCHEMA extensions;

Then try it:

    SELECT hostname();

Dependencies
------------
The `hostname` extension requires PostgreSQL 9.0 or higher and the POSIX API, `<unistd.h>`
