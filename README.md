# C Linux Development Environment

A personal C development environment and learning setup for **Linux systems programming, networking, debugging, profiling, and low-level development**.

This repository documents the tools, libraries, and workflow I use while learning C and Linux.

---

## Why This Setup?

The goal is not just to learn C syntax.

I want to understand how programs actually work on Linux:

- How C programs are compiled
- How executables are built
- How memory is managed
- How programs interact with the Linux kernel
- How system calls work
- How libraries are linked
- How programs are debugged
- How performance problems are identified
- How networking libraries are used
- How databases and XML are handled from C
- How larger C projects are built and documented

---

# Environment

- OS: Ubuntu 26.04 LTS
- Environment: WSL2
- Shell: Bash
- Editor: Vim
- Architecture: x86_64

Check your environment:

```bash
lsb_release -a
uname -r
```

---

# Core Development Tools

## GCC

GCC is the C compiler.

It converts C source code:

```text
main.c
   ↓
 GCC
   ↓
 executable
```

Check installation:

```bash
gcc --version
```

Basic compilation:

```bash
gcc main.c -o program
```

Useful options:

```bash
gcc -Wall -Wextra -g main.c -o program
```

### Options

`-Wall`

Enables common compiler warnings.

`-Wextra`

Enables additional warnings.

`-g`

Adds debugging information so debuggers such as GDB can understand the source code.

`-o program`

Specifies the name of the output executable.

---

# Make

Make automates compilation.

Instead of repeatedly typing long GCC commands, the commands are stored in a `Makefile`.

Example:

```makefile
CC = gcc

CFLAGS = -Wall -Wextra -g

program: main.c
	$(CC) $(CFLAGS) main.c -o program

clean:
	rm -f program
```

Build:

```bash
make
```

Clean:

```bash
make clean
```

The purpose of Make is to make builds repeatable and easier to manage.

---

# GDB

GDB is the GNU debugger.

It is used when a program:

- crashes
- produces incorrect results
- has unexpected behavior
- needs to be inspected while running

Start GDB:

```bash
gdb ./program
```

Useful commands:

```text
break main
run
next
step
print variable
continue
quit
```

Example:

```gdb
break main
run
next
print x
continue
```

---

# Valgrind

Valgrind is used to detect memory-related problems.

It can detect things such as:

- memory leaks
- invalid memory access
- use-after-free
- invalid reads/writes

Run:

```bash
valgrind --leak-check=full ./program
```

For example, if memory is allocated:

```c
int *p = malloc(sizeof(int));
```

but never freed:

```c
free(p);
```

Valgrind can report the leak.

---

# gprof

gprof is a traditional function-level profiler.

It helps determine which functions are consuming execution time.

Compile with profiling support:

```bash
gcc -pg main.c -o program
```

Run:

```bash
./program
```

Then analyze:

```bash
gprof ./program
```

The important idea is:

```text
Compile with profiling
        ↓
Run program
        ↓
Collect profiling data
        ↓
Analyze with gprof
```

---

# strace

`strace` shows the **system calls** made by a program.

This is extremely useful for understanding how applications interact with the Linux kernel.

Run:

```bash
strace ./program
```

You may see calls such as:

```text
openat(...)
read(...)
write(...)
mmap(...)
close(...)
```

For example:

```bash
strace -e trace=openat,read,write,close ./program
```

This allows me to observe what the operating system is doing underneath my C program.

---

# ltrace

`ltrace` shows calls made to shared libraries.

Run:

```bash
ltrace ./program
```

Conceptually:

```text
strace → system calls
ltrace → library calls
```

This helps understand the boundary between my program and external libraries.

---

# pkg-config

`pkg-config` helps find the compiler and linker flags required by installed libraries.

For example:

```bash
pkg-config --cflags --libs libcurl
```

Instead of manually finding:

- header locations
- library locations
- linker flags

`pkg-config` provides the required information.

Example:

```bash
gcc main.c $(pkg-config --cflags --libs libcurl) -o program
```

---

# CMake

CMake is a build-system generator.

It is useful for larger projects where manually maintaining Makefiles becomes inconvenient.

Instead of directly describing every compiler command, a project can describe its build requirements in:

```text
CMakeLists.txt
```

Then CMake generates the appropriate build files.

---

# Ninja

Ninja is a fast build system.

It is commonly used together with CMake for fast incremental builds.

Example workflow:

```bash
cmake -G Ninja -S . -B build
cmake --build build
```

---

# Doxygen

Doxygen generates documentation from source-code comments.

Example:

```c
/**
 * @brief Adds two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return Sum of a and b.
 */
int add(int a, int b);
```

Generate a configuration file:

```bash
doxygen -g
```

Generate documentation:

```bash
doxygen Doxyfile
```

Doxygen can generate HTML and other documentation formats.

---

# C Libraries

The development packages below provide headers and linker information needed to compile C programs against these libraries.

---

## libcurl

Used for network communication, especially HTTP/HTTPS.

Install:

```bash
sudo apt install libcurl4-openssl-dev
```

Include:

```c
#include <curl/curl.h>
```

Compile:

```bash
gcc main.c $(pkg-config --cflags --libs libcurl) -o program
```

Useful for learning:

- HTTP
- APIs
- networking
- downloading data
- client applications

---

# GLib

GLib provides reusable C data structures and utilities.

Install:

```bash
sudo apt install libglib2.0-dev
```

Example:

```c
#include <glib.h>
```

Useful features include:

- hash tables
- dynamic arrays
- strings
- queues
- lists
- utility functions

---

# GSL

GSL means **GNU Scientific Library**.

Install:

```bash
sudo apt install libgsl-dev
```

It provides mathematical and scientific functionality.

Example:

```c
#include <gsl/gsl_math.h>
```

Useful for:

- numerical calculations
- statistics
- mathematics
- scientific programming

---

# SQLite3

SQLite is a small embedded SQL database.

Install:

```bash
sudo apt install libsqlite3-dev
```

Include:

```c
#include <sqlite3.h>
```

Useful for learning:

- databases
- SQL
- persistence
- database APIs from C

---

# libxml2

libxml2 is an XML parsing library.

Install:

```bash
sudo apt install libxml2-dev
```

Include:

```c
#include <libxml/parser.h>
#include <libxml/tree.h>
```

Useful for:

- XML parsing
- processing structured data
- understanding parser libraries

---

# Complete Installation

The complete development environment can be installed with:

```bash
sudo apt update

sudo apt install -y \
    build-essential \
    gdb \
    valgrind \
    gprof \
    pkgconf \
    doxygen \
    strace \
    ltrace \
    git \
    cmake \
    ninja-build \
    libcurl4-openssl-dev \
    libglib2.0-dev \
    libgsl-dev \
    libsqlite3-dev \
    libxml2-dev
```

---

# Verify Installation

Run:

```bash
gcc --version
make --version
gdb --version
valgrind --version
gprof --version
pkg-config --version
doxygen --version
strace --version
ltrace --version
git --version
cmake --version
ninja --version
```

---

# Typical C Development Workflow

The tools are used for different problems.

```text
                    Write C code
                         │
                         ▼
                       GCC
                    Compile code
                         │
                         ▼
                       Make
                  Automate builds
                         │
                         ▼
                      Program
                         │
          ┌──────────────┼──────────────┐
          ▼              ▼              ▼
         GDB          Valgrind        strace
       Debugging       Memory        System calls
                       errors
          │
          ▼
       gprof / perf
       Performance
          │
          ▼
       ltrace
    Library calls
```

Libraries are added when the program needs functionality that is not provided by the C standard library.

```text
Program
  │
  ├── libcurl   → HTTP/networking
  ├── GLib      → data structures/utilities
  ├── GSL       → mathematics
  ├── SQLite3   → database
  └── libxml2   → XML
```

---

# Git

Git is used to track changes to the source code.

Initialize a repository:

```bash
git init
```

Configure Git identity:

```bash
git config --global user.name "Your Name"
git config --global user.email "your@email.com"
```

Add files:

```bash
git add .
```

Commit:

```bash
git commit -m "message"
```

Connect a GitHub repository:

```bash
git remote add origin git@github.com:USERNAME/REPOSITORY.git
```

Push:

```bash
git push -u origin main
```

---

# SSH Authentication

SSH is used to authenticate my computer with GitHub without using a GitHub password for every Git operation.

Generate an SSH key:

```bash
ssh-keygen -t ed25519 -C "your@email.com"
```

Public key:

```bash
cat ~/.ssh/id_ed25519.pub
```

The public key can be added to GitHub.

The private key:

```text
~/.ssh/id_ed25519
```

must remain private.

Test authentication:

```bash
ssh -T git@github.com
```

---

# Learning Goals

This environment is intended for learning:

- Modern C
- Linux internals
- Linux system calls
- Networking
- TCP/IP
- Sockets
- Memory management
- Processes
- Threads
- Concurrency
- Operating-system concepts
- Performance analysis
- Debugging
- Low-level programming

The goal is to understand not only **how to write C programs**, but also **what the operating system and hardware are doing underneath them**.
