# Custom Page Fault Handling Program 

### By Nathaniel Hoaglund

## Overview of work accomplished

This program takes in no command line arguments. When it starts it asks a user to enter in a number between 0 and 3.
Given the input number, it will trigger a page fault either on page 0, 1, 2, or 3 of the memory it is looking at.
This page fault information is then given to the server and the server returns a quote from the following movies:
0 - star wars 
1 - harry potter 
2 - devil wears prada
3 - lord of the rings 

Which then gets put into the corresponding page which caused the page fault. Once that page is in memory, it will not cause another page fault
to try and view the same quote.

## Running Instructions

To create this program, run `make build` from the command line. This will create a `fault` and `pg_server` executable.

Next run `sudo make run` which will run both `pg_server` and `fault`. It does this by running `pg_server` in the background. 
The program will ask the user to input a number between 0 and 3. If -1 is inputted the program closes. Ctrl-C can also close the program.

To then kill the server, you can run `sudo make teardown`. Both these commands require sudo permissions.

`make clean` removes the executables. Running `sudo make clean` will also terminate the server running in the background.


## List of source files
pg_fault.c
pg_fault.h
pg_server.c
pg_server.h


