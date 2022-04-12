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

That said, The section "Things about C/C++" mostly don't apply to
other languages.

Introduction
------------

Debugging
.........

Debugging is the skill of identifying why a program does something
unexpected. There is a bug when the user expects something to happen,
but the program does something different. It could be something very
clear, like throwing an exception, or it could be a misleading UI or
weird interaction between parts of the program.

We will mainly concentrate on tools that allow you to find issues and
inspect the internal state of you program as it run.

Debugging in five steps
.......................

1. Identify an issue

   * Find a problem or receive a report from a user.
   * Get a Segmentation Fault.
   * Find an issue using an analysis tool.

2. Isolate the bug

   * Reproduce the problem
   * Create a minimal case that causes the problem to occur.
   * (Turn this into a test case)

3. Find the erroneous logic

   * This can be in a single location, or an interaction between
     different parts of the code

4. Fix the bug

   * Replace the bad code or redo logic

5. Test

   * Check that the bug is no longer reproduced
   * Check that **everything** that used to work still works.

We will mostly concentrate on finding the problem in the code. How you
find an issue or receive a report depends a lot on your project and is
not language specific.

When you publish your code, make sure to include a way for users to
communicate back to you. For example, if you are using a public
service such as Github, Gitlab or Bitbucket enable issues.



Things about C/C++
------------------

Datatypes: Static and strong(ish) typing
........................................

C and C++ are statically typed. This means you specify the type of each variable
when it is first created and the type cannot be changed. This protects you from
a lot of problems you might run into in other languages.

Typing in C and C++ is also (relatively) strong. Types do not get cast into
other types automatically. But both have implied casting rules. For example,
assigning to a variable of a different type can work, but results in a cast.

You can also cast a pointer to a different type. Doing this can easily cause
memory issues and is almost always a bad idea. The main reason you would ever
want to do this has to do with micromanaging memory for a slight performance
gain.

Compilers will often assume that the type information that comes with pointers
is correct. So if something works at optimization level 0 and 1, but you get
a segfault on level 2 or 3, maybe you are casting a pointer?

Pointers
........

Talking of pointers, they are commonly cited as the hardest thing to understand
in C and C++. The main problem with pointers is that they allow you to do bad
things by mistake. In fact, you often have to actively do something (free
memory) to avoid doing bad things.

At its core, a pointer is a variable that contains an address in memory. In C,
this is really all it is. In modern C++, you have a choice between a few
pointer types that are all safer than the basic C pointer.

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


Errors and Exceptions
---------------------

Manual error handling in C
..........................

C has no built-in error handling, but there are libraries for this. The most
common approach is that each function returns and integer error code. By
convention 0 means success and any other number refers to an error. The caller
can check the error code and handle it.

You can use an `enum` to give each error code a sensible name. You can also use
an array to map each error code to a message string

.. code-block:: C

    enum ERROR_CODES {
      MYLIB_SUCCESS,
      MYLIB_IO_ERROR,
      MYLIB_PARAMETER_ERROR,
      MYLIB_LITERARY_ERROR,
      MYLIB_OTHER_ERROR
    };

    string error_messages[] = {
      "Success",
      "An IO error was encountered.",
      "My lib received an incorrect parameter.",
      "A literary error was found in input parameters.",
      "An unexpected error was encountered."
    }

In worst cases, when you don't think the program can recover, you can always
call `exit(1)` (or any other error code besides 1). You should print and error
message first.


C++ Exceptions
..............

There is a bit more structure around this in C++. Especially, you can catch an
exception and handle it in code.

Throwing an exception looks like this:

.. code-block:: C++

    double divide(x, y){
        if(y == 0){
           throw "Division by 0 exception"
        }
        return x/y
    }

By default this will stop the program and print the message. The other option
is to handle it in code using the `try` syntax:

.. code-block:: C++

      double try_to_divide(x, y){
          try {
            result = divide(x,y);
            return result;
          } catch (const char* message){

            // Return infinity if dividing by zero
            return x * std::numeric_limits<double>::infinity();
          }
      }




Finding Memory Issues
---------------------

In this section we will demonstrate two useful tools for studying your code,
**Valgrind** and **DrMemory**. We will mainly use them to find memory problems,
but they are actually more versatile than that. Checkout
`Valgrind <https://valgrind.org/>`_ and
`DrMemory <https://drmemory.org/page_install.html>`_
for more details.

Valgrind
........

Valgrind essentially wraps your program and intercepts calls to kernel
functions. This means your code will run significantly slower, especially when
full memory checks are enabled. It's recommended to use a small test case if
your program usually takes a long time to run.

First, you should compile your code with

.. code-block:: console

      $ CC -g code.c -o executable

where CC is your c compiler. The `-g` flag adds source files and line numbers
in the compiled executable, allowing valgrind to report where it finds problems.

Next, run Valgrind with

.. code-block:: console

      $ valgrind --leak-check=full --tool=memcheck ./executable

This should point out any memory issues in you code.

Take a look at ``examples/memory_leak.c``. The function named ``memory_fail``
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



Debugging
---------

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



