#!/usr/bin/env python

"""
Author: Eric Zair
File: run.py
Created on: 08/29/2019
Description:    Super simple python3 script that removes the build/ dir and
                then calls make. In the event that make generates the main
                executable, we execute the program.
"""
import subprocess
from os.path import exists


""" Set this to the path of the executable you want to run """
PATH_TO_BUILDABLE_EXECUTABLE = 'build/vssh-b'


def main():
    """
    Check that all pre-conditions are met, so that we can execute and
    properly build our executable file.
    """
    # We can't run the make command if there is no make file,
    # so we just quit the program.
    if not exists('Makefile'):
        SystemExit('Error, missing make file! '
                   'Please create a Makefile before executing this script')

    # We want to make sure that we only run the make command in the event
    # that the executable is actually generated newly.
    # To make sure it is newly generated, we make sure it is not there before
    # calling make'. Funny pun: make sense...?
    if exists('build/'):
        subprocess.call(['rm', '-rf', 'build'])
    subprocess.call('make')

    # PATH_TO_BULDABLE_EXECUTABLE should exist after the above make call.
    # However, if it does not, then we know that there was a compilation
    # issue, so we do nothing.
    if exists(PATH_TO_BUILDABLE_EXECUTABLE):
        # We don't wanna see all the messy input from the build,
        # because at this point we KNOW it was successful,
        # as the executable file is there.
        subprocess.call('clear')
        subprocess.call(PATH_TO_BUILDABLE_EXECUTABLE)


if __name__ == '__main__':
    main()
