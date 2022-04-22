
Errors and Exceptions
=====================

Manual error handling in C
--------------------------

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

.. code-block:: C

   int error_code = my_function();
   if(error_code){
     printf("Error: %s\n", error_messages[error_code]);
     exit(1);
   }


- Always check for possible errors and print the error message.
- Another convention: Many Unix system calls return `-1` if there was an
  error and `errno` is set to an error code.

So read the manual for the library you are using.


C++ Exceptions
--------------

There is a bit more structure around this in C++. Especially, you can catch an
exception and handle it in code.

Throwing an exception looks like this:

.. code-block:: C++

    double divide(double x, double y){
        if(y == 0){
           throw std::runtime_error("Division by 0");
        }
        return x/y;
    }

By default this will stop the program and print the message. The other option
is to handle it in code using the `try` syntax:

.. code-block:: C++

      double try_to_divide(x, y){
          try {
            double result = divide(x,y);
            return result;

          } catch (std::runtime_error &){
            // Return infinity if dividing by zero
            return x * std::numeric_limits<double>::infinity();
          }
      }

The above will catch everything that inherits `std::runtime_error`. You can
create a custom exception type by extending `std::exception` and catch only that.

