Exercises
=========

Exercise 1: A segfault
----------------------

Compile and run either
`segfault.c <https://raw.githubusercontent.com/rantahar/debugging-c-cpp/main/examples/segfault.c>`_
or
`segfault.cpp <https://raw.githubusercontent.com/rantahar/debugging-c-cpp/main/examples/segfault.cpp>`_.
It should cause a segfault.

1. What tool would you use to find the problem?
2. Identify the issue. What should the program actually do?
3. Fix the program and test it.


Exercise 2: Divide by Zero (C++)
--------------------------------

Try compiling and running
`divide_by_zero.cpp <https://raw.githubusercontent.com/rantahar/debugging-c-cpp/main/examples/divide_by_zero.cpp>`_.
This one throws an exception rather than just running along with incorrect
results. That's nice.

- How would you go about finding the cause of the exception?
- Use a debugger to inspect the code and look at the values passed to the
  function. What is the problem?
- How would you fix the issue?

Exercise 3: The double pendulum (C)
-----------------------------------

This exercise is longer than the others and the code is more complex. If you
brought your own code to debug, I suggest you look at that instead.

The code is at
`double_pendulum.c <https://raw.githubusercontent.com/rantahar/debugging-c-cpp/main/examples/double_pendulum.c>`_
It runs a simulation
of a double pendulum. It has some problems, though.

1. **Compilation errors**

Try compiling the program with

.. code-block:: console

    $ cd examples
    $ gcc -g -O2 double_pendulum.c -lm -o double_pendulum

The code does not compile. Can you find the problems following hints from
the compiler or your IDE?

2. **Segfault**

Once you manage to compile it, run the program with

.. code-block:: console

    $ ./double_pendulum

Now there's a segmentation fault! Use a debugger
to find where the segfault happens. Can you fix it?

Looks like it works! But does it, actually?

3. **Memory leak**

You have received complaints from users. When the program runs for a long
time, it takes a lot of memory. Maybe there is a memory leak.

.. Hint::
   You can separate valgrind output (and other errors) to a file using

   .. code-block:: console

      $ valgrind --leak-check=full double_pendulum 2> valgrind_errors


4. **More?**

Can you find another memory issue?

.. Hint::
   Use `valgrind tool=memcheck` and let the simulation run for a while.

.. Hint::
   What happens when a pendulum does not fit on the screen?
