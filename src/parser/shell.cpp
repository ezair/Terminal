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
        if (exists_and_is_exe("/bin/" + path_to_exe))
            path_to_exe = "/bin/" + path_to_exe;

        else if (exists_and_is_exe("/usr/local/bin/" + path_to_exe))
            path_to_exe = "usr/local/bin/" + path_to_exe;

        else if (exists_and_is_exe("/usr/bin/" + path_to_exe))
            path_to_exe = "/usr/bin/" + path_to_exe;
        else
            cout << "BAD" << endl;

        execl(path_to_exe.c_str(),
              this->vector_of_strings_to_array(command_args),
              (const char*) nullptr);
    }
    return 0;
}


char* const Shell::vector_of_strings_to_array(vector<string> vec) {
    char** const array_of_command_args = new char * [vec.size()];
    for (unsigned int i = 0; i < vec.size(); i++) {
        char* const token_command_arg = new char[vec[i].size() + 1];
        strcpy(token_command_arg, vec.at(i).c_str());
        array_of_command_args[i] = token_command_arg;
    }
    return *array_of_command_args;
}


bool Shell::exists_and_is_exe(string path_to_program) {
    return exists(path_to_program) &&
           access(path_to_program.c_str(), X_OK) == 0;
}
