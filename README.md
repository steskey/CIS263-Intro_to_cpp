# CIS 263 Homework 1 - **Introduction to C++**

This assignment is meant to help you get used to coding very simple C++ while learning about ```std::vector<>```s, ```std::string```s, git and Github, and software testing.

First though, we should talk about the concept of executable files and the process by which they are created.

## Executable files

Every computer has a processor.  The processor controls everything the computer does by following coded instructions.  Giving processors instructions was tricky historically because of the variance in codes for different processors and the low-level of abstraction at the processor level.  Higher-level languages were created that could provide advanced levels of abstraction and could be used on multiple different architectures.  These capabilities were the result of the creation of compilers.  Compilers would take a higher-level language and translate it into code the individual processors could understand.

For instance, a compiler might take the C
```
#include <stdio.h>

int main(int argc, char** argv){
  printf("Hello world!\n");
}

```

and convert it into something like this:

```
.section	__TEXT,__text,regular,pure_instructions
.macosx_version_min 10, 12
.globl	_main
.p2align	4, 0x90
_main:                                  ## @main
.cfi_startproc
## BB#0:
pushq	%rbp
Ltmp0:
.cfi_def_cfa_offset 16
Ltmp1:
.cfi_offset %rbp, -16
movq	%rsp, %rbp
Ltmp2:
.cfi_def_cfa_register %rbp
subq	$32, %rsp
leaq	L_.str(%rip), %rax
movl	%edi, -4(%rbp)
movq	%rsi, -16(%rbp)
movq	%rax, %rdi
movb	$0, %al
callq	_printf
xorl	%ecx, %ecx
movl	%eax, -20(%rbp)         ## 4-byte Spill
movl	%ecx, %eax
addq	$32, %rsp
popq	%rbp
retq
.cfi_endproc

.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
.asciz	"Hello world!\n"


.subsections_via_symbols
```

Note that this is really assembly code, and still not processor or machine code.  It is used here to provide some level of human-readability.  In reality it looks more like

```
... (Code omitted)
0002000 11 22 10 51 00 00 00 00 11 40 64 79 6c 64 5f 73
0002010 74 75 62 5f 62 69 6e 64 65 72 00 51 72 00 90 00
0002020 72 10 11 40 5f 70 72 69 6e 74 66 00 90 00 00 00
0002030 00 01 5f 00 05 00 02 5f 6d 68 5f 65 78 65 63 75
0002040 74 65 5f 68 65 61 64 65 72 00 21 6d 61 69 6e 00
0002050 25 02 00 00 00 03 00 d0 1e 00 00 00 00 00 00 00
0002060 d0 1e 00 00 00 00 00 00 02 00 00 00 0f 01 10 00
0002070 00 00 00 00 01 00 00 00 16 00 00 00 0f 01 00 00
0002080 50 0f 00 00 01 00 00 00 1c 00 00 00 01 00 00 01
0002090 00 00 00 00 00 00 00 00 24 00 00 00 01 00 00 01
00020a0 00 00 00 00 00 00 00 00 02 00 00 00 03 00 00 00
00020b0 00 00 00 40 02 00 00 00 20 00 5f 5f 6d 68 5f 65
... (Code omitted)
```

The point though, is that this code can be executed by the processor.  We have created an executable file.

### Header files (include files) and libraries (lib files)

Computer scientists realized early on they needed higher levels of abstraction.  It is easier to write code that has functions for commonly performed tasks than it is to rewrite the same code many times over.  Additionally, functions used in one piece of code may often be useful to other pieces of code as well.  Suppose you are writing the ```printf()``` code from the above example.  You figure out how to tell the processor to print some string to the console.  Once you perfect that function, it makes more sense to have some mechanism to use that code in your next project than it does to reproduce the functionality.  Even better - if there are really commonly needed functions they can be pre-compiled and included on the system.  These pre-compiled bits of code are called "libraries".

By default, the code in these libraries are not included in our own files.  Instead, a program called the "linker" links our code to the library.  This is called "dynamic linking" and allows us to keep our files smaller.  However, we can also do "static linking" which pulls the code from the library to put directly into our executable.

Pre-compiled code is not human readable (as you can see from above).  So how do programmers know how to use the functions provided in the libraries?  Usually the interface for working with these libraries are included in "header files".  In C++ (and C) header files are named with the ```.h``` extension.  A sample header follows:

```
#ifndef   __H_MY_HEADER__
#define   __H_MY_HEADER__

void doSomething(int x, int y);

#endif
```

A few important things to see in this code:
  - We have a function signature (**declaration**) but no actual code for how the function should work (**definition**).  So, we know how to call the function and what it returns, but we have NO IDEA how it accomplishes the task.
  - The #ifndef, #define, and #endif statements are pre-processor directives.  Directives give the compiler special instructions.  Together, these three directives form what is called an "include guard".  We will talk about this further below.

Now, we know how to use the ```doSomething()``` function.  We don't know how it works (and we don't need to!), and we can use it in our own code.  We would do this by putting the directive

```
#include "my_header.h"    // If this is a local bit of code

OR

#include <my_header>      If this is a system library
```

in any file that wishes to use that functionality.

### Include Guards

In your mind you may be thinking of compilation as taking a single file and producing a single executable.  This is not usually what happens however.  In reality the compiler must compile every file separately.  If you have a file called ```main.cpp```, one called ```my_functions.cpp```, and one called ```my_functions.h``` and your ```main.cpp``` includes ```my_functions.h```, then your compiler must compile ```main.cpp``` and ```my_functions.cpp``` separately.  The linker then creates an executable by linking them together.  Usually this happens with a single command which obfuscates the process a bit.

But what happens if you want to use a function such as the ```printf()``` function but one of your libraries also wants to use the ```printf()``` function?  More specifically, what if you have the directive
```
#include <stdio.h>
```
in ```main.cpp``` but also make use of ```my_functions.cpp``` which includes the same directive?  Do we want our final executable to have multiple copies of the function?  Of course not!  This would be redundant and violate the very spirit of the abstraction we are trying to accomplish.  Enter the idea of "**include guards**".  Include guards prevent code that has already been sourced in from being sourced in again.

Common questions about this process are:

  Q. ***If you are using the functions from ```my_functions.cpp``` in your ```main.cpp``` file, how does the compiler know you are using them correctly?***

  A.  By including the ```my_functions.h``` header file we include the declarations of the functions we are going to use.  The declaration tells us the name, type, and parameter types (if any) of our functions.  This is all the information the compiler needs.

  Q.  ***Why do we sometimes use quotes ("") and other times use angle brackets (<>) in our #include statements?***

  A.  We use quotes for our local files and angle brackets for system libraries.

  Q.  ***If we can dynamically link to libraries what is the purpose of static linking?***

  A.  We statically link when we want to run the code on a target system that might not have the libraries we need, or the versions we need.  This ensures our code can still run.

  Q.  ***I've heard that instead of include guards we can use the ```#pragma once``` directive to include a file only once.  Why aren't we using that?***

  A.  This directive isn't part of the C++ standard (at least not yet).  It is true that it is implemented by many compilers, but as it isn't standardized we don't know what issues might arise as we use it with different compilers.

  ## Assignment

### Setup

  Each of these tasks will be illustrated in class as well.

1.  Your first task is to create a Github account, if you do not currently have one.  [Github](https://github.com "Github.com").

2.  Create a Travis-CI account.  [Travis-CI](https://travis-ci.org/ "Travis-CI.org").

3.  At the top of this repository is a "Fork" link (alternatively you can click [Here](https://github.com/irawoodring/CIS263-Intro_to_cpp#fork-destination-box "Link to fork this repo in your own account.")). This will create a forked copy of this repository in your account.

4.  Sync your Github account with Travis-CI by clicking the "Sync" button on the top right of the Travis-CI main page.  This will cause all of your repositories to show up in Travis-CI.

5.  Turn on testing for your copy of this repository by clicking the virtual switch beside the repo in the repo listing on Travis-CI.  Once this is complete, every time you push your repository to Github the tests will automatically run.

### Programming tasks

Now it is time to program in C++!  In class today we learned about creating simple objects in C++.  We learned about how C++ handles strings (```std::string```) and how we can use a vector (```std::vector<>```) to store dynamically sized collections of objects.  This assignment will give you the opportunity to practice these concepts.

The project you cloned has all of the files you need to complete this assignment.  ```main.cpp``` uses the Catch framework to test our code and make sure it is running correctly.  I have included test cases to make sure the code is running correctly.  If a test runs correctly, you can be given full credit for the problem (doesn't mean you always will!).  If a test case fails, you can receive no credit for that problem.  I will be inspecting the code that you turn in to make sure that even though the tests pass that the code doesn't have any other issues.

You must complete the following functions (signatures taken directly from the ```my_functions.h``` file).  As you are implementing code for which an interface is already defined, you will be putting your code in the ```my_functions.cpp``` file.  Please note that this file is already created for you, and is located in the ```src/``` directory, whereas the interface file is in ```include/```.

1.  ```std::string createString();``` - this function takes no parameters and returns a ```std::string``` that holds the value "Hello world!";

2.  ```std::vector<std::string> createVector();``` - this function takes no parameters and returns a new ```std::vector<std::string>``` to hold our strings.

3.  ```int putStringsInVector(int num);``` - this function takes one parameter ```int num```.  It calls our previous two functions to get a new vector and to place ```num``` versions of the string returned from ```createString()``` into the vector.  For instance, if we call ```putStringsInVector(42);``` we should have the value ```42``` returned from the function.

4.  ```void modifyVector(std::vector<int> & vector);``` - this function will take a **reference** to a vector of ints.  This means that we can modify the vector as if it were a local variable, and the changes will persist after the function is gone.  To complete this function you should modify every fifth element in the vector to the value ```42```.
