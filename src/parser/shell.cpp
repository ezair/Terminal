/**
 * @author Eric Zair
 * @file shell.cpp
 * @brief File containing the class definitions for our Shell class
 *        located inside of the "shell.h" file.
 * @version 0.1
 * @date 2019-09-01
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "shell.h"

#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::string;
using std::cin;
using std::cout;
using std::getline;
using std::vector;
using std::stringstream;
using std::endl;
using std::strcat;
using std::filesystem::exists;
using std::filesystem::path;


vector<string> Shell::vector_of_tokens_parsed_from_string(string str) {
    vector<string> parsed_tokens_from_str;
    stringstream token_in_str(str);
    // Add each token to this vector, since it will be used later on in
    // loop method.
    while (token_in_str >> str)
        parsed_tokens_from_str.push_back(str);
    return parsed_tokens_from_str;
}

int Shell::loop() {
    while (1) {
        cout << this->prompt_location << " ";
        string user_input = "";

        // In the event that we reach a EOF, wanna break our loop
        // and go back into the main where the program will exit.
        if (!getline(cin, user_input))
            break;

        // We need to grab the user input, since it must be parsed
        // and searched for a specific keyterm. To do this, it is
        // best to use a vector, as we can store every single user input
        // token given.
        vector<string> command_args =
            this->vector_of_tokens_parsed_from_string(user_input);

        // In the event that the user just hits the enter key without
        // typing anything, the list will be at length 0, which is a
        // problem, since we access it's indexes multiple times after
        // this line of code.
        // Thus, we put this below statement here so that we ignore
        // all below code  if the list is size == 0.
        if (command_args.size() == 0)
            continue;

        // When "exit" is given alone, we should quit
        if (command_args.at(0) == "exit" && command_args.size() == 1)
            return 0;

        char** const command_args_as_array =
            vector_of_strings_to_array(command_args);
        string path_to_exe = command_args.at(0);

        if (path_to_exe[0] == '/') {
           execute_program(path_to_exe.c_str(), command_args_as_array);
        }
        else if (exists_and_is_exe("/bin/" + path_to_exe)) {
            path_to_exe = "/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(), command_args_as_array);
        }
        else if (exists_and_is_exe("/usr/local/bin/" + path_to_exe)) {
            path_to_exe = "usr/local/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(), command_args_as_array);
        }
        else if (exists_and_is_exe("/usr/bin/" + path_to_exe)) {
            path_to_exe = "/usr/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(), command_args_as_array);
        }
        else if (command_args.at(0) == "cd") {
            if (command_args.size() >= 2)
                this->change_directory(command_args[1]);
            // The way the linux cd command works: if the user does NOT
            // provide a second argument the program goes to home.
            else
                this->change_directory("~");
        }
        else
            cout << "BAD" << endl;

        // We need to clean up all memory to avoid dumb leaks.
        command_args.clear();
        path_to_exe.clear();
        delete[] command_args_as_array;
    }
    return 0;
}


void Shell::change_directory(string directory) {
    char cwd[sizeof(directory.c_str())];
    chdir(directory.c_str());
    (getcwd(cwd, sizeof(cwd)));
    string temp(cwd);
    this->prompt_location = temp;
    cout << this->prompt_location << "I am here" << endl;
}


char** const Shell::vector_of_strings_to_array(vector<string> vec) {
    char** const array_of_command_args = new char * [vec.size()];
    for (unsigned int i = 0; i < vec.size(); i++) {
        char* const token_command_arg = new char[vec[i].size() + 1];
        strcpy(token_command_arg, vec.at(i).c_str());
        array_of_command_args[i] = token_command_arg;
    }
    return array_of_command_args;
}


bool Shell::exists_and_is_exe(string path_to_program) {
    return exists(path_to_program) &&
           access(path_to_program.c_str(), X_OK) == 0;
}


int Shell::execute_program(string path_to_exe, char** const command_args) {
    pid_t child_pid = fork();

    // Error occured with forking.
    if (child_pid < 0)
        return -1;

    if (child_pid != 0) {
        pid_t terminating_pid = 0;
        int exit_status = 0;

        while (terminating_pid != child_pid)
            terminating_pid = wait(&exit_status);

        if (WIFEXITED(exit_status) && (WEXITSTATUS(exit_status) != 0))
            return WEXITSTATUS(exit_status);
    }
    else {
       execv(path_to_exe.c_str(), command_args);
    }
    return 0;
}
