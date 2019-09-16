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

#include <unistd.h>
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
    string prompt_location;

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

    /**
     * @brief Takes a vector<string> and returns it as a char array
     * of strings.
     *
     * @param vec The vector that we want to return a char*[] version of.
     *
     * @return char* const char*[] containing all the same string values
     *                             as the passed in vec parameter.
     */
    char** const vector_of_strings_to_array(vector<string> vec);

    /**
     * @brief Return if the program at a given path exists and is an exe.
     *
     * @param path_to_program location of the program that a user wants
     *                        to see if it exists.
     * @return true if file exists and is an exe
     * @return false if file does not exists or file is not an exe.
     */
    bool exists_and_is_exe(string path_to_program);

    /**
     * @brief Fork and execute a given program.
     *
     * @param path_to_exe Path to the program you want to execute.
     * @param command The program command that you want to run.
     *
     * @return int -1 if failure.
     * @return int 0 if success.
     */
    int execute_program(string path_to_exe, char** const command);


 public:
    /**
     * @brief Construct a new Shell object.
     * This shell object simply emulates that of a terminal.
     */
    Shell() {
        char cwd[1024];
        (getcwd(cwd, sizeof(cwd)));
        string temp(cwd);
        this->prompt_location = temp + "$";
    }

    /**
     * @brief Destroy the Shell object.
     */
    ~Shell() {
        this->prompt_location.clear();
    }

    /**
     * @brief Waits for a user to enter a command. We then check if the
     * command is valid and in the event that it is we simply execute it.
     *
     * @return int  success code: 0 if no issues, 1 otherwise.
     */
    int loop();

    /**
     * @brief Change directory in shell to a given location.
     *
     * @param directory Location to move to in the shell.
     */
    void change_directory(string directory);
};

#endif  // SRC_PARSER_SHELL_H_
