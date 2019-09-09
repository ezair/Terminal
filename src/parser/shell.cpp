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


int Shell::returnCode() {
    // Currently we only want to return the code for success.
    // This will change later on (more than likely).
    return 0;
}

vector<string> Shell::vector_of_tokens_parsed_from_string(string str) {
    vector<string> parsed_tokens_from_str;
    stringstream token_in_str(str);
    // Add each token to this vector, since it will be used later on in
    // loop method.
    while (token_in_str >> str)
        parsed_tokens_from_str.push_back(str);
    return parsed_tokens_from_str;
}

void Shell::loop() {
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

        for (unsigned int i = 0; i < command_args.size(); i++) {
            if (command_args.at(i) == "exit")
                return;
            cout << "word[" << i << "] = " << command_args.at(i) << endl;
        }
        cout << endl;
    }
}
