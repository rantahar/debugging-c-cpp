.. Debugging C documentation master file, created by
   sphinx-quickstart on Wed Jan 19 17:12:23 2022.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Debugging C/C++
===============

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Prerequisites
-------------

 - C or C++. You should have written C or C++ code,
   compiled an executable and run it.
 - command line interface or VS Code. You should know how to
   move to a folder, list files, compile
 - See `here <https://aaltoscicomp.github.io/linux-shell/the-shell/>`_ for an introduction to the Linux shell.

Installation
------------

 - You should have a C / C++ compiler installed.
 - Install a debugger.

    - Linux and Mac: gdb. This is installed with C/C++ compilation tools.
    - Windows: Visual Code with the C/C++ extension.
 - Install a memory checker

    - `Valgrind <https://valgrind.org/>`_ on Linux or Mac.
    - `DrMemory <https://drmemory.org/page_install.html>`_ on Windows.
      You can also try this on other systems.

Learning Outcomes
-----------------

After this course you will
 - Know which tools to use to inspect your code and find problems (or
   know where to check which tools to use).
 - Know what a segmentation fault is and be able to locate it.
 - Be able to use a debugger (after finding references online).
 - Be able to find memory leaks and other memory issues.

Most of this course applies directly to Fortran and other compiled
languages. Each language has their own quirks and common problems,
but the same tools can be used to solve them.

That said, in the first section we will talk about special the quirks of
C and C++, which may or may not apply to other languages.


Things about C/C++
------------------

Datatypes: Strong and static typing
...................................

C and C++ are strongly typed. This means you specify the type of each variable
when it is first created and the type cannot be changed. This protect you from
a lot of problems you might run into in other languages.

That said, you can cast a pointer to a different type. Doing this can easily
cause memory issues and is almost always a bad idea. The main reason you would
ever want to do this has to do with micromanaging memory for a slight
performance gain.

Compilers will often assume that the type information that comes with pointers
is correct. So if something works at optimization level 0 and 1, but you get
a segfault on level 2 or 3, maybe you are casting a pointer?

Pointers
........

Talking of pointers, they are commonly cited as the hardest thing to understand
in C and C++. At its core, a pointer is a variable that contains an address in
memory. In C, this is really all it is. In modern C++, you have a choice between
a few pointer types that are all safer than the basic C pointer.

Memory issues are probably the most common problems you will face in C, and are
common in C++ as well. Memory issues include

  - Segmentation faults: You program tries to read or write to the wrong place
    in memory. These are generally easy to debug, since they happen on a
    specific line in the code.
  - Memory leaks: The program reserves memory and does not release it. If it
    runs for a long time, this reduces system performance and may cause a crash.
  - Misreads and -writes: The program uses the same memory for two different
    things. Data gets overwritten incorrectly.

C++ pointer types:
 - std::unique_ptr: There is ever only one pointer that points to this memory.
   The memory is automatically freed, so that memory does not leak.
 - std::shared_ptr: A pointer that tracks references to the memory it points to.
   When there are no more references, the memory is freed.
 - std::weak_ptr: A reference to a std::shared_ptr that is not counted. This is
   sometimes necessary to avoid circular dependencies, but should be avoided if
   not otherwise.
 - std::auto_ptr (deprecated since C++11): Automatically allocates memory and
   releases it when the pointer goes out of scope.


Errors and Signals
------------------

C has no built-in error handling, but there are libraries for this.
Ultimately this comes down to printing an error message and calling
`exit(1)` (or any other error code besides 1).


Finding Memory Issues
---------------------

There are many tools for identifying memory issues. Here we will use valgrind
(https://valgrind.org/), a general tool for instrumenting and analysing
compiled programs.

Valgrind essentially wraps your program and intercepts calls to kernel
functions. This means your code will run significantly slower, especially when
full memory checks are enabled. It's recommended to use a small test case if
your program usually takes a long time to run.


.. code-block:: console

      $ valgrind --leak-check=full --tool=memcheck ./memory

Valgrind has many other tools, besides Memcheck. See https://valgrind.org/ for
more details


Debugging with gdb
------------------

The Gnu debugger (gdb), and many other similar programs, allow you to stop your
program and inspect the state different variables, or even modify them before
continuing the run. This is useful for finding more complicated issues.

Here are some useful gdb commands:

  - **list:** Print a few lines of code around the current position.
  - **where:** Print the current position and the functions that were called
    to get there (same as the stack trace printed when an exception is raised).
  - **next:** Execute the current line and move to the next one.
  - **step:** If the line contains a function, move into it. Otherwise execute
    the current line.
  - **continue:** Run until the next `pdb.set_trace`
  - **up**: Move to the function that called this one (up the stack).
  - **down**: Move to the function called from this one (down the stack).
  - **display variable:** Dispaly the value of a variable. It will be printed after each command.



Defensive Programming Assertions
--------------------------------

- Assertions

- Exceptions in C++


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
