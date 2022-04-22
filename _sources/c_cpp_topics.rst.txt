Things about C/C++
==================

Datatypes: Static and strong(ish) typing
----------------------------------------

 - The type of a variable does not change
 - But you can assign to a variable of a different type and the conversion is
   often implicit.
 - Pointers can be assigned with abandon (but should not be.)

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
--------

 - Commonly cited as the hardest part in C (and sometimes C++), but they are
   necessary for most programs.
 - Common issues.
 - C++ has useful pointer types.

Talking of pointers, they are commonly cited as the hardest thing to understand
in C and C++. The main problem with pointers is that they allow you to do bad
things by mistake. In fact, you often have to actively do something (free
memory) to avoid doing bad things.

At its core, a pointer is a variable that contains an address in memory. In C,
this is really all it is. In modern C++, you have a choice between a few
pointer types that are all safer than the basic C pointer.

Memory issues are probably the most common problems you will face in C, and are
common in C++ as well. Memory issues include

  - **Segmentation faults**: You program tries to read or write to the wrong
    place in memory. These are generally easy to debug, since they happen on a
    specific line in the code.
  - **Memory leaks**: The program reserves memory and does not release it. If it
    runs for a long time, this reduces system performance and may cause a crash.
  - **Misreads and -writes**: The program uses the same memory for two different
    things. Data gets overwritten incorrectly.
  - **Uninitialized reads**: Program reads memory before writing to it. This
    results in some random content for the variable.

These can all be debugged using `Valgrind` or `drMemory`, which we will show in
the next section.

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

Note: Don't mix smart pointers with arrays. When the smart pointer goes out of
scope, it calls delete and the contents of the array can get deallocated.


Macros
------

- Macros can contain arbitrary code.
- It's easy to create a syntax error. The macro content is directly pasted in.

To see what a macro call actually does, use

.. code-block:: console

    $ gcc -E code.c

The output will include all the header files, so it might be quite long.


Misplaced semicolon
-------------------

Sometimes things that should not work actually do:

.. code-block:: C

    c = 0;
    while(c<10); {
      c++;
    }

Note the semicolon after `while`. This is an infinite loop.

C and C++ have an interesting modular structure, where most things are
statements that return a value. The while loop below can be executed without any
brackets to the right. Similarly, the brackets can be executed independently of
anything to their left (they group statements into a single statement).


Virtual functions and inheritance
---------------------------------

 - Confusing base class functions and derived class functions

Virtual function can be binded at runtime based on the reference type to an
object. They are used to achieve runtime polymorphism. This means you need to
track what type the object reference is to figure out what function gets called.

The best way to avoid problems is to give function descriptive names to make it
clear what they are doing applying to. The function `get_name` of a derived
class should not be different from the function `get_name` of the base class.

 - Memory leak due to missing virtual destructor

If you handle memory dynamically, you should usually add a virtual destructor.
A standard destructor does not get called when a derived class object gets
destroyed.

The following may not call the destructor for MyClass:

.. code-block:: C++

    class MyClass : public MyBase {
      ~MyClass(){}
    }

    Myclass a = new MyClass();
    MyBase *b = a
    delete b;

- Polymorphism only works for references. If you pass by value or make a copy,
  in the base class, information of derived classes is lost.

.. code-block:: C++

    MyClass a;
    Baseclass b = a;       // if you make a copy
    b.my_class_function(); // this does not work



Returning by Reference or Pointer
---------------------------------

Using pointers (C) and references (C++) to return values removes a copy
operation. This can affect performance, especially in C++ where a copy can call
a constructor.

The problem is when you return something from the function scope, and it gets
deallocated immediately on return:

.. code-block:: C

    double * divide(x, y){
      double result = x/y;
      return &result;
    }

- A bit more subtle example in C++:

.. code-block:: C

    class MyClass {
      double a;
      public:
      MyClass(){
        a=1;
      }
      double &get_a(){
        return a;
      }
    };

    int main(){
      MyClass *myClass = new MyClass();
      double &a = myClass->get_a();
      std::cout << a << std::endl; // 1
      delete myClass;
      std::cout << a << std::endl; // 0 or some random value
    }

- Note that most compilers optimize the copy away in any case.


Exception in a Destructor
-------------------------

We will talk more about exceptions later, but here is an example of how things
can go wrong:

.. code-block:: C++

    class MyClass {
      double * a;
      MyClass(){
        a = malloc(100*sizeof(int));
      }
      ~MyClass(){
        do_something(a); // What if this throws an exception?
        free(a);
      }
    };

This is a problem if the exception is caught. The `free` function was never
called.


Using a freed pointer or old reference
--------------------------------------

Very similar to above. This happens when you fetch a pointer or a reference to
memory handled by a library. If the library decides to re-allocate the memory,
or to move to pointer for any other reason, your pointer will no longer work.

.. code-block:: C++

    std::vector<float> v = {1,2,3,4};
    float * pointer = v.data();
    a.push_back(4);
    std::cout << pointer[2] << std::endl; // this might not work

