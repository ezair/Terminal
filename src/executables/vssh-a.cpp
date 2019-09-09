/**
 * @author Eric Zair
 * @file vssh-a.cpp
 * @brief This program simulates that of a terminal.
 *        A user can enter terminal commands and have them executed.
 *        This file is the main file of the project.
 * @version 0.1
 * @date 2019-08-29
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <iostream>
#include <cstdio>
#include <string>
#include "../parser/shell.h"


int main(int argc, char const *argv[]) {
    Shell shell;
    shell.loop();
    return shell.returnCode();
}
