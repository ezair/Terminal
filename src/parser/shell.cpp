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
#include <bits/stdc++.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "shell.h"

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
    while (true) {
        string user_input = "";
        cout << this->shell_prompt_name << " ";

        // In the event that we reach a EOF, we exit the program.
        if (!getline(cin, user_input))
            break;

        // We need to grab the user input, since it must be parsed
        // and searched for a specific keyterm. To do this, it is
        // best to use a vector, as we can store every single user input
        // token given.
        vector<string> command_args =
            this->vector_of_tokens_parsed_from_string(user_input);

        // Bye bye, user.
        if (command_args.at(0) == "exit")
            return 0;

        string path_to_exe = command_args.at(0);

        // Empty condition, nothing needs to be done here.
        if ((path_to_exe.find("/") || path_to_exe.find("./")) &&
                                      exists_and_is_exe(path_to_exe)) {
           execute_program(path_to_exe.c_str(),
                           this->vector_of_strings_to_array(command_args));
        }
        else if (exists_and_is_exe("/bin/" + path_to_exe)) {
            path_to_exe = "/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(),
                            this->vector_of_strings_to_array(command_args));
        }
        else if (exists_and_is_exe("/usr/local/bin/" + path_to_exe)) {
            path_to_exe = "usr/local/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(),
                            this->vector_of_strings_to_array(command_args));
        }
        else if (exists_and_is_exe("/usr/bin/" + path_to_exe)) {
            path_to_exe = "/usr/bin/" + path_to_exe;
            execute_program(path_to_exe.c_str(),
                            this->vector_of_strings_to_array(command_args));
        }
        else
            cout << "BAD" << endl;
    }
    return 0;
}


char** const Shell::vector_of_strings_to_array(vector<string> vec) {
    char** const array_of_command_args = new char * [vec.size()];
    for (unsigned int i = 0; i < vec.size(); i++) {
        char* const token_command_arg = new char[vec[i].size() + 1];
        strcpy(token_command_arg, vec.at(i).c_str());
        array_of_command_args[i] = token_command_arg;
    }
    // array_of_command_args[vec.size() - 1] = NULL;
    return array_of_command_args;
}


bool Shell::exists_and_is_exe(string path_to_program) {
    return exists(path_to_program) &&
           access(path_to_program.c_str(), X_OK) == 0;
}


int Shell::execute_program(string path_to_exe, char** const command_args) {
    pid_t child_pid = fork();
    if (child_pid) {
        pid_t terminating_pid = 0;
        int exit_status;

        while (terminating_pid != child_pid)
            terminating_pid = wait(&exit_status);

        if (WIFEXITED(exit_status) && (WEXITSTATUS(exit_status) != 0))
            return WEXITSTATUS(exit_status);
    }
    else
        execv(path_to_exe.c_str(), command_args);
    return 0;
}
