/**
 * @author Eric Zair
 * @file shell.h
 * @brief Header file containing all of the definitions for the
 *        Shell class/object that we are making.
 * @version 0.1
 * @date 2019-09-02
 *
 * @copyright Copyright (c) 2019
 */
#ifndef SRC_PARSER_SHELL_H_
    #define SRC_PARSER_SHELL_H_

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief This class represents that of a terminal for the linux OS.
 * We are essentially emulating what a terminal can do (but in a much
 * more simplistic case).
 */
class Shell {
 private:
    /**
     * @brief This is the text that is displayed on the side of the
     * shell. You can think of it as the user's username that will be
     * displayed inside of the shell.
     */
    string shell_prompt_name;

    /**
     * @brief This is the return code signaling whether or not
     * the program executed properly.
     *
     */
    int return_code;

    /**
     * @brief Given a string string, we parse each token in it
     * (seperated by spaces) and add each token to a vector.
     * We then simply return that vector.
     *
     * @param str The string that we want to parse and add each
     *            token to this vector.
     * @return vector<string> -- contains all of the tokens from
     *                           the passed in string.
     */
    vector<string> vector_of_tokens_parsed_from_string(string str);

 public:
    /**
     * @brief Construct a new Shell object.
     * This shell object simply emulates that of a terminal.
     *
     */
    Shell() {
        this->shell_prompt_name = "vssh-a$";
    }

    /**
     * @brief Destroy the Shell object.
     *
     */
    ~Shell() {
        // Default Destructor.
    }

    /**
     * @brief Loop through and wait for a user to enter commands via
     *        user input. We then take those commands and execute them.
     *
     */
    void loop();

    /**
     * @brief Returns the return code of the shell.
     * 0 means that we did not run into any issues.
     * 1 implies that we ran into some issues.
     *
     * @return The status code of whether or not the program
     *         executed correctly.
     *
     */
    int returnCode();
};

#endif  // SRC_PARSER_SHELL_H_
