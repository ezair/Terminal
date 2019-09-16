#!/usr/bin/env python

"""
Author:	Eric Zair
File: test/test.py
Super Simple test script to check that our own programs
can be executed as well.
"""
from sys import argv


def test():
    """
    Prints a quick test test print statement out.
    """
    print("this is a really really really simple test")


def main():
    """
    Execute very simple test.
    """
    test()
    # This is a possible syste flag to the program.
    if '--test' in argv:
        print('--test was given as a sys argument.')


if __name__ == '__main__':
    main()
