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

 - Familiarity with C or C++. You should have written C or C++ code,
   compiled an executable and run it.
 - Familiarity with a command line interface. You should know how to
   move to a folder and list files. You can also use an IDE for
   debugging, but we will not cover any specific IDE.
    - See `here <>`_ for an introduction to the Linux shell.

Installation
------------

 - You should have a C / C++ compiler installed.
 - Please also install `Valgrind <>`_ on Linux or
   `DrMemory <>`_ on Windows. See `installation instructions <>`_
   for details.

Learning Outcomes
-----------------

After this course you will
 - Know which tools to use to inspect your code and find problems (or
   know where to check which tools to use).
 - Be able to use a debugger (after finding references online).
 - Know what a segmentation fault is and be able to locate it.
 - Be able to find memory leaks and other memory issues.


Most of this course applies directly to Fortran and other compiled
languages. Each language has their own quirks and common problems,
but the same tools can be used to solve them.

That said, in the first section we will talk about special the quirks of
C and C++, which may or may not apply to other languages.


Things about C/C++
------------------


 - Pointers
   - Memory problems are probably the most common errors
   -
 - Types
   - protect from many issues
   - often problems result from overriding the type system (casting pointers)


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
