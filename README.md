# ID Block Information

* @author Eric Zair
* @email zairea200@potsdam.edu
* @course CIS 310 Operating Systems
* @assignment p002
* @due 09/11/2019

## Program Description

Goal: To turn vssh-a from a simple string processor (that extracts wordsfrom lines of text) into a shell.A shell (like sh, bash, csh, etc.)

1. Prompts the user.

2. Keeps track of the current working directory (cwd).

    (a) The prompt often indicates the current working directory.

3. Reads input a line at a time.

    (a) Most (not ours) support some sort of line continuation for longer commands.

4. Extracts the words from the command-line

    (a) The first word is assumed to name a command (executable file) to run.

    (b) Remaining words are command-line parameters passed into the command.

5. Search apath(list of standard paths) for the named command.

6. Execute the standard command, waiting until the command finishes, and looping backto the prompt.

## How To Run

There are 2 very simple ways to execute this program.

## The run.py script

Inside of the base directory there is a file called run.py

Essentially, this file removes current version of the build/ dir (if it exists) and the calls make, makes sure that it properly works. Assuming that the make command does work, the script then executes the main program `build/vssh-b`.

To run the run.py script, simply run the following command:

`./run.py`

## Directly Calling The vssh-b program

The other way to run the program is to call the following command:

`make;./build/vssh-b`

This will build and run the program.

## Doxygen & Documentation

Comments in this program are done in a format that supports using doxygen to generate .html documentation.

### Generating Doxygen Documentation

To Generate doxygen documentation make sure that doxygen is proeprly installed on your system.

If it is not installed on your system and you are running linux, run the following command:

`sudo apt-get install doxygen`

This will install doxygen on your computer.

Now that doxygen is installed on your computer, you can run the following command to generate the documentation:

`cd doc; doxygen Doxyfile`

Once executed, the documentation will be generated successfully.

## Testing

NOTE: Normally I would create/build unit tests for testing purposes, however, that feels a bit overkill for this assignment.

### Testing Cases Used

1. The case where a user uses a command such as `ls`:

    ``` Bash
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls
    build  doc  Makefile  program  README.md  run.py  src
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls -a
    .   build  .git        Makefile  README.md  src
    ..  doc    .gitignore  program	 run.py     .vscode
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b
    ```

2. The case where the user uses the `cd` command:

    ``` Bash
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls
    build  doc  Makefile  program  README.md  run.py  src
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b cd src
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b/src ls
    allModule.mk  executables  parser
    ```

3. The case where the user uses the `cd` command to back a directory e.g. `cd ..`:

    ```Bash
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls
    build  doc  Makefile  program  README.md  run.py  src
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b cd src
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b/src ls
    allModule.mk  executables  parser
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b/src
    ```

4. The case where a user runs a script in their current directory:

    ```Bash
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls
    build  doc  Makefile  program  README.md  run.py  src  test.py
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b /test.py
    this is a really really really simple test
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b
    ```

5. The case where a user a test program in the same directory with command line argument:

    ```Bash
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b ls
    build  doc  Makefile  program  README.md  run.py  src  test.py
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b /test.py --test
    this is a really really really simple test
    --test was given as a sys argument.
    /home/ez/Workspace/Classes/OS/p002/CIS-310-vssh-b
    ```
