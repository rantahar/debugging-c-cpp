
Finding Memory Issues
=====================

In this section we will demonstrate two useful tools for studying your code,
**Valgrind** and **DrMemory**. We will mainly use them to find memory problems,
but they are actually more versatile than that. Checkout
`Valgrind <https://valgrind.org/>`_ and
`DrMemory <https://drmemory.org/page_install.html>`__
for more details.

Valgrind
--------

.. note::
   Valgrind does not work on Windows directly, but you can use it with a
   terminal or Linux emulator such as
   `WSL <https://docs.microsoft.com/en-us/windows/wsl/>`_ or
   `cygwin <https://www.cygwin.com/>`_.

   Program compiled in these emulators will usually not work on native windows,
   but you can debug and study the code.


Valgrind essentially wraps your program and intercepts calls to kernel
functions. This means your code will run significantly slower, especially when
full memory checks are enabled. It's recommended to use a small test case if
your program usually takes a long time to run.

First, you should compile your code with

.. code-block:: console

      $ gcc -g code.c -o executable

The `-g` flag adds source files and line numbers
in the compiled executable, allowing valgrind to report where it finds problems.

Next, run Valgrind with

.. code-block:: console

      $ valgrind --leak-check=full --tool=memcheck ./executable

This should point out any memory issues in you code.

Take a look at
`memory_leak.c <https://raw.githubusercontent.com/rantahar/debugging-c-cpp/main/examples/memory_leak.c>`_.
The function named ``memory_fail``
will allocate some memory and then lose the pointer. Let's see if valgrind will
catch this.

.. code-block:: console

      $ cd examples
      $ gcc -g memory_leak.c -o memory_leak
      $ valgrind --leak-check=full --tool=memcheck ./memory_leak

      ==105525== Memcheck, a memory error detector
      ==105525== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
      ==105525== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
      ==105525== Command: ./memory_leak
      ==105525==
      ==105525==
      ==105525== HEAP SUMMARY:
      ==105525==     in use at exit: 40 bytes in 1 blocks
      ==105525==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
      ==105525==
      ==105525== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
      ==105525==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
      ==105525==    by 0x109161: memory_fail (memory_leak.c:6)
      ==105525==    by 0x109192: main (memory_leak.c:13)
      ==105525==
      ==105525== LEAK SUMMARY:
      ==105525==    definitely lost: 40 bytes in 1 blocks
      ==105525==    indirectly lost: 0 bytes in 0 blocks
      ==105525==      possibly lost: 0 bytes in 0 blocks
      ==105525==    still reachable: 0 bytes in 0 blocks
      ==105525==         suppressed: 0 bytes in 0 blocks
      ==105525==
      ==105525== For lists of detected and suppressed errors, rerun with: -s
      ==105525== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

We see the problem report after the ``HEAP SUMMARY`` block (40 bytes ...
definitely lost ...). It confirms the leak is in ``memory_leak.c`` on line 6.

Valgrind can provide a lot more information than just memory checks. For example
it can instrument and profile your code with the `callgrind` and `cachegrind`
tools. See the `manual <https://valgrind.org/docs/manual/manual.html>`_ for a
lot more detail.


drMemory
--------

.. note::
   `drMemory <https://drmemory.org/index.html>`_ memory debugger
   that also works on Windows. You will still need to prepare the application.
   See their `prep application page <https://drmemory.org/page_prep.html>`_ for
   details.


If you use Windows you probably did not prepare the application yet. If you use
the Visual Studio compiler, you need to add the `/Zi` flag and recompile. In
Visual Studio Code, go to "Settings" (press `ctrl+,`) and search for "compiler".
Add the flag to "C_Cpp Default: Compiler Args".

Running drMemory works similarly to Valgrind:

.. code-block:: console

      $ drmemory -- memory_leak

      ~~Dr.M~~ Dr. Memory version 2.5.0
      ~~Dr.M~~
      ~~Dr.M~~ Error #1: LEAK 40 direct bytes NULL0007f06c6ad8ff0-NULL0007f06c6ad9018 + 0 indirect bytes
      ~~Dr.M~~ # 0 replace_malloc               [/home/runner/work/drmemory/drmemory/common/alloc_replace.c:2580]
      ~~Dr.M~~ # 1 memory_fail                  [/u/24/rantahj1/unix/src/c-debugging/examples/memory_leak.c:6]
      ~~Dr.M~~ # 2 main                         [/u/24/rantahj1/unix/src/c-debugging/examples/memory_leak.c:12]
      ~~Dr.M~~
      ~~Dr.M~~ ERRORS FOUND:
      ~~Dr.M~~       0 unique,     0 total unaddressable access(es)
      ~~Dr.M~~       0 unique,     0 total uninitialized access(es)
      ~~Dr.M~~       0 unique,     0 total invalid heap argument(s)
      ~~Dr.M~~       0 unique,     0 total warning(s)
      ~~Dr.M~~       1 unique,     1 total,     40 byte(s) of leak(s)
      ~~Dr.M~~       0 unique,     0 total,      0 byte(s) of possible leak(s)
      ~~Dr.M~~ ERRORS IGNORED:
      ~~Dr.M~~      13 unique,    16 total,   6682 byte(s) of still-reachable allocation(s)
      ~~Dr.M~~          (re-run with "-show_reachable" for details)
      ~~Dr.M~~ Details: /u/24/rantahj1/unix/bin/DrMemory-Linux-2.5.0/drmemory/logs/DrMemory-memory_leak.18987.000/results.txt

