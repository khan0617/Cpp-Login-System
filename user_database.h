#ifndef USER_DATABASE_H
#define USER_DATABASE_H

#include <unordered_map>
#include <iostream>
#include <string_view>
#include "json.hpp"
using json = nlohmann::json;

/**
 *  @brief Prompt the user for password input. Once received, load the "password" parameter with this new data.
 *  @param password_setup: When true, the user will be prompted twice to confirm their password (used when setting up a password).
 *  @param password: The configured password will be loaded into this string reference.
 *  @return The hash of the password.
 */
size_t get_password(std::string& password, bool password_setup);


/**
 *  @brief Prompt the user to enter a username, which will be loaded into parameter "username".
 *  @param username: output of this function is stored in this variable.
 *  @return 0 if the user enters "quit", else 1.
 */
int get_username(std::string& username);


/**
 *  @brief Prompts the user to enter their age, which will be loaded into parameter "age".
 *  @param age: Output of this function.
 *  @return 0 if the user typed "quit" else 1. 
 */
int get_age(int& age);

/**
 *  @brief Get all user data for creating a new user: username, password, age.
 *  @param username: Will be loaded with the entered username. Output for the username field.
 *  @param password: Output parameter for the password field.
 *  @param age: Output parameter for the age field.
 *  @param ask_for_age: If true, prompt the user to enter their age otherwise don't.
 *  @param password_setup: If true, prompt the user to confirm their password by typing it twice.
 *  @return 0 if either of the inputs are "quit", -1 on failure, 1 on success.
 */
int get_user_data(std::string& username, std::string& password, int& age, bool ask_for_age, bool password_setup = false);

/**
 *  @brief Prompt the user to input "y" or "n". If invalid, keep prompting for input in the terminal.
 *  @return -1 if user enters "quit", 1 of user enters "y", 0 for "n".
 */
int get_user_choice();


/**
 *  @brief Displays the admin menu, allowing users to see usersname of everyone else, or delete users.
 *  @param data: A json object loaded with information from users.json.
 *  @return 0 if the ever wants to logout, -1 if they want to quit, else 1.
 */
int admin_menu(json& data);


/**
 *  @brief Display all options for the current menu.  
 *  @param menu_type: The type of help menu to show. Valid types are "admin", "user", and "invalid_login".
 */
void show_help_menu(std::string_view menu_type);


/**
 *  @brief Outputs all users in the database to the console.
 *  @param data: A json object loaded with information from users.json.
 */
void show_users(json& data);


/**
 *  @brief Displays the standard user menu. Here, users can change their username, password, or age.
 *  @param data: A json object loaded with information from users.json.
 *  @return 0 if the user enters "quit", 1 otherwise.
 */
int user_menu(json& data);


/**
 *  @brief Displays the main menu of the program, prompting username/password input.
 *  @param data: A json object with information from parsing users.json
 *  @return 0 if the user enters "quit", else 1.
 */
int main_menu(json& data);

/**
 *  @brief Allows an admin to input a username/password combination to add them to the database.
 *  @param data: A json object with information from parsing users.json
 *  @return 0 if the user is done with this menu, -1 to quit, else 1 to keep adding users. 
 */
int add_user_as_admin(json& data);


/**
 *  @brief Allows a user to add themselves to the database.
 *  @param new_user: Output parameter which is loaded with the new user's username.
 *  @param data: A json object with information from parsing users.json
 */
int add_user(json& data, std::string& new_user);

/**
 *  @brief Allows admin to delete a user from the database, by username.
 *  @param data: A json object with information from parsing users.json
 *  @return 0 if the admin is done deleting, -1 to quit the program, else 1 to keep deleting. 
 */
int delete_user(json& data);


/**
 *  @brief Change the password of the user specified by "username".
 *  @param data: A json object with information from parsing users.json
 *  @param username: The username we'd like to change the password of. 
 *  @return 0 on Success, -1 if the username does not exist, 1 if passwords didn't match.
 */
int change_password(json& data, std::string_view username);

/**
 *  @brief Change the age of the user specified by "username".
 *  @param data: A json object with information from parsing users.json
 *  @param username: The username we'd like to change the age of. 
 *  @return -1 on failure, else 0.
 */
int change_age(json& data, std::string_view username);

#endif