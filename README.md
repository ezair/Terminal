# ID Block Information
* @author Eric zair
* @email zairea200@potsdam.edu
* @course CIS 310 Operating Systems
* @assignment p001
* @due 09/4/2019


# Program Description

The purpose of this program is to create a "Shell" class in C++.

Essentially, the Shell class will take in user input in the form of a string. The shell will then break the given user input into individual tokens. These tokens must then be checked and compared against the string "exit", as we when the "exit" token is given, we exit the program.

NOTE: The main program will return status code from the Shell class. If the return code is 0, then we have no errors. If the return code is not 0...well, we have issues.

# How To Run

There are 2 very simple ways to execute this program.

## The run.py script

Inside of the base directory there is a file called run.py

Essentially, this file removes current version of the build/ dir (if it exists) and the calls make, makes sure that it properly works. Assuming that the make command does work, the script then executes the main program `build/vssh-a`.

To run the run.py script, simply run the following command:

`./run.py`

## Directly Calling The vssh-a program

The other way to run the program is to call the following command:

`make;./build/vssh-a`

This will build and run the program.

# Doxygen & Documentation

Comments in this program are done in a format that supports using doxygen to generate .html documentation.

## Generating Doxygen Documentation

To Generate doxygen documentation make sure that doxygen is proeprly installed on your system.

If it is not installed on your system and you are running linux, run the following command:

`sudo apt-get install doxygen`

This will install doxygen on your computer.

Now that doxygen is installed on your computer, you can run the following command to generate the documentation:

`cd doc; doxygen Doxyfile`

Once executed, the documentation will be generated successfully.

# Testing

NOTE: Normally I would create/build unit tests for testing purposes, however, that feels a bit overkill for this assignment.

## Testing Cases Used

In terms of testing cases, I tested the following strings passed in by the user:

1. The case where "something something something" is givne as a string input.

        Output:
            ```
            vssh-a$ something something something
            word[0] = something
            word[1] = something
            word[2] = something
            ```

2. The case where "                x     y     z" is given in as a string:
        Output:
            ```
            vssh-a$                 x     y     z
            word[0] = x
            word[1] = y
            word[2] = z
            ```

3. The case where " saomethingadiasdsai               y                 c         exit" is given as a string input:

        Output:
            ```
            vssh-a$  saomethingadiasdsai               y                 c         exit
            word[0] = saomethingadiasdsai
            word[1] = y
            word[2] = c
            ```

4. The case where "something exit something" is given as a string input:
        Output:
            ```
            vssh-a$ something exit something
            word[0] = something
            ```

5. The case where "ctrl+d" is given as a string input:
        Output:
            ```
            vssh-a$ ez@ez-Inspiron ~/Workspace/Classes/OS/p001 $
            ```
