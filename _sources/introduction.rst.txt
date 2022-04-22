Introduction
============

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
    - `DrMemory <https://drmemory.org/page_install.html>`__ on Windows.
      You can also try this on other systems.

Learning Outcomes
-----------------

After this course you will
 - Know which tools to use to inspect your code and find problems (or
   know where to check which tools to use).
 - Know what a segmentation fault is and be able to locate it.
 - Be able to use a debugger (after finding references online).
 - Be able to find memory leaks and other memory issues.

The tools used on this course are also used to debug Fortran and other compiled
languages. Each language has their own quirks and common problems, so the first
sections do not apply.


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

1. **Identify an issue**

   * Find a problem or receive a report from a user.
   * Get a Segmentation Fault.
   * Find an issue using an analysis tool.

2. **Isolate the bug**

   * Reproduce the problem
   * Create a minimal case that causes the problem to occur.
   * (Turn this into a test case)

3. **Find the erroneous logic**

   * This can be in a single location, or an interaction between
     different parts of the code

4. **Fix the bug**

   * Replace the bad code or redo logic

5. **Test**

   * Check that the bug is no longer reproduced
   * Check that **everything** that used to work still works.

We will mostly concentrate on finding the problem in the code. How you
find an issue or receive a report depends a lot on your project and is
not language specific.

When you publish your code, make sure to include a way for users to
communicate back to you. For example, if you are using a public
service such as Github, Gitlab or Bitbucket enable issues.