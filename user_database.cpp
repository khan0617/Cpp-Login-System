#include "user_database.h"

int admin_menu(json& data){
    std::cout << "Enter an option (help to se choices again): ";
    std::string input;
    std::cin >> input;
    if(input == "show"){
        show_users(data);
    }

    // Keep running add_user_admin() until user is done (they write "quit" or "n")
    else if(input == "add"){
        int run_add{};
        while((run_add = add_user_as_admin(data))){
            if(run_add == -1){
                return -1;
            }
        }
    }
    else if(input == "delete"){
        int run_delete{};
        std::cout << "Show list of users? (y/n): ";
        if(get_user_choice()){
            show_users(data);
        }
        while((run_delete = delete_user(data))){
            if(run_delete == -1){
                return -1;
            }
        }
    }
    else if(input == "logout"){
        return 0;
    }
    else if(input == "quit"){
        return -1;
    }
    else if(input == "help"){
        show_help_menu("admin");
    }
    else if(input == "clear"){
        std::system("clear");
    }
    else{
        std::cout << "Invalid option received: " << input << ". Try again.\n";
        show_help_menu("admin");
    }

    return 1;
}

int user_menu(json& data, std::string_view username){
    std::cout << "Enter an option (help to see choices again): ";
    std::string input;
    std::cin >> input;
    if(input == "password"){
        int pass_change{};
        while((pass_change = change_password(data, username))){
            if(pass_change == -1){
                return -1;
            }
        }
    }
    else if(input == "age"){
        if(change_age(data, username) == -1){
            return -1;
        }
    }
    else if(input == "quit"){
        return -1;
    }
    else if(input == "logout"){
        return 0;
    }
    else if(input == "clear"){
        std::system("clear");
    }
    else{
        std::cout << "Invalid option received: " << input << ", Try again.\n";
        show_help_menu("user");
    }
    return 1;
}

int change_age(json& data, std::string_view username){
    int age{};
    std::cout << "Enter your desired age: ";
    std::cin >> age;
    if(!data.contains(username)){
        std::cout << "Username " << username << " doesn't exist! Failted to change age.\n";
        return -1;
    }
    data[username]["age"] = age;
    return 0;
}

int get_age(int& age){
    bool invalid_age = false;
    std::string tmp_age;
    do{
        if(invalid_age){
            std::cout << "Invalid age received. Try again.\n";
        }
        std::cout << "Enter your age: ";
        std::cin >> tmp_age;
        try{
            age = std::stoi(tmp_age);
            invalid_age = false;
        } catch(...){
            if(tmp_age == "quit"){
                return 0;
            }
            invalid_age = true;
        }
    } while(invalid_age);
    return 1;
}

int get_username(std::string& username){
    std::cout << "Enter a username: ";
    std::cin >> username;
    if(username == "quit"){
        std::cout << "Username cannot be \"quit\", terminating program....\n";
        return 0;
    }
    return 1;
}

size_t get_password(std::string& password, bool password_setup){
    bool wrong_password = false;
    std::string tmp_password;
    std::hash<std::string> hasher;

    // if password_setup is true, then we want to ask the user to confirm their password.
    // if false, we're simply asking them for a password upon login.
    if(password_setup){
        do{
            if(wrong_password){
                std::cout << "Passwords didn't match. Try again.\n";
            }
            std::cout << "Enter your password: ";
            std::cin >> password;
            std::cout << "Confirm password: ";
            std::cin >> tmp_password;
            wrong_password = (tmp_password != password) ? true : false;
        } while(wrong_password);
    }
    else{
        std::cout << "Enter your password: ";
        std::cin >> password;
    }

    return hasher(password);
}

int change_password(json& data, std::string_view username){
    std::string password;
    std::hash<std::string> hasher;
    if(!data.contains(username)){
        std::cout << "Username " << username << " doesn't exist! Failed to change password.\n";
        return -1;
    }
    get_password(password, true);
    data[username]["password"] = hasher(password);
    std::cout << "Password successfully updated!\n";
    return 0;
}

int add_user_as_admin(json& data){
    int age{};
    std::string username, password;
    std::hash<std::string> hasher;
    if(!get_user_data(username, password, age, true, true)){
        return -1; // User sent "quit".
    }
    if(data.contains(username)){
        std::cout << "Username already exists, please try another username.\n";
        return 1;
    }
    else{
        data[username]["password"] = hasher(password);
        data[username]["age"] = age;
        std::cout << "User " << username << " sucessfully registered. Add another? (y/n): ";
        return get_user_choice();
    }
}

int add_user(json& data){
    int age{};
    std::string username, password;
    std::hash<std::string> hasher;
    if(!get_user_data(username, password, age, true, true)){
        return -1; // User sent "quit".
    }
    if(data.contains(username)){
        std::cout << "Username already exists, please try another username.\n";
        return 1;
    }
    data[username]["password"] = hasher(password);
    data[username]["age"] = age;
    std::cout << "Successfully registered! Logging in...\n";
    return 0;
}

int delete_user(json& data){
    std::string input;
    std::cout << "Enter username to delete (exit to go to the previous menu): ";
    std::cin >> input;
    if(input == "quit"){
        return -1;
    }
    else if(input == "exit"){
        return 0;
    }
    else if(!data.contains(input)){
        std::cout << "Provided username does not exist, please try again.\n";
        return 1; // Return 1 to keep running delete_users()
    }
    else if(input == "admin"){
        std::cout << "Cannot delete admin user! Please try again.\n";
    }
    else{
        data.erase(input);
        std::cout << "Sucessfully removed user. Remove another? (y/n): ";
        return get_user_choice();
    }
    return 0;
}

int get_user_choice(){
    // Assume that the user has alerady been prompted to enter "y/n" before calling this function.
    std::string input;
    std::cin >> input;
    while(input != "quit" && input != "y" && input != "n"){
        std::cout << "Invalid input. Please enter y, n, or quit: ";
        std::cin >>input;
    }
    if(input == "quit"){
        return -1;
    }
    return (input == "y") ? 1 : 0;
}

int get_user_data(std::string& username, std::string& password, int& age, bool ask_for_age, bool password_setup){
    if(!get_username(username)){
        return 0;
    }
    get_password(password, password_setup);
    if(ask_for_age && !get_age(age)){
        return 0;
    }
    return 1;
}

void show_help_menu(std::string_view menu_type){
    if(menu_type == "admin"){
        std::cout << "Available Admin Options:\n"
            << "    add - Add a username/password combination to the database.\n"
            << "    delete - Delete a user from this database.\n"
            << "    help - Show this help menu again.\n"
            << "    show - Show list of all users in this database.\n"
            << "    logout - Return to the main login screen.\n"
            << "    clear - Clear the terminal window.\n"
            << "    quit - Terminate the program.\n";
    }
    else if(menu_type == "user"){
        std::cout << "Available User Options:\n"
            << "    password - Change your password.\n"
            << "    age - Change your age.\n"
            << "    help - Show this help menu again.\n"
            << "    logout - Return to the login menu.\n"
            << "    clear - Clear the terminal window.\n"
            << "    quit - Terminate the program.\n";
    }
    else if(menu_type == "invalid_login"){
        std::cout << "Invalid username or password. Options:\n"
            << "    login - Try to login again.\n"
            << "    register - Register a username/password for the first time.\n"
            << "    quit - Terminate the program.\n";
    }
    else{
        std::cout << "Invalid menu type: " << menu_type << std::endl;
    }
}

void show_users(json& data){
    for(auto it : data.items()){
        std::cout << "  " << it.key() << ", age: " << data[it.key()]["age"] << "\n";
    }
    std::cout << std::endl;
}

int main_menu(json& data){
    std::cout << "-----Login menu-----\n";
    std::hash<std::string> hasher;
    std::string username{}, password{}, input{};
    int age{};
    if(!get_user_data(username, password, age, false)){
        return 0;
    }

    size_t hashed_password = hasher(password);

    if(username == "admin" && hashed_password == data["admin"]["password"]){
        int run_admin{};
        show_help_menu("admin");
        while((run_admin = admin_menu(data))){
            if(run_admin == -1){
                return 0;
            }
        }
    }
    else if(!data.contains(username) || data[username]["password"] != hashed_password){
        show_help_menu("invalid_login");
        std::cout << "Enter your option: ";
        std::cin >> input;
        if(input == "login"){
            return 1;
        }
        else if(input == "quit"){
            return 0;
        }
        else if(input == "register"){
            int run_add{}, run_login{};
            std::string new_user;
            while((run_add = add_user(data, username))){
                if(run_add == -1){
                    return 0;
                }
            }
            std::cout << "Welcome, " << username << "! ";
            show_help_menu("user");
            while((run_login = user_menu(data, username))){
                if(run_login == -1){
                    return 0;
                }
            }
        }
        else{
            std::cout << "Invalid input. Going back to login menu...\n";
            return 1;
        }
    }
    else if(data.contains(username) && data[username]["password"] == hashed_password){
        int run_login{};
        std::cout << "Welcome, " << username << "! ";
        show_help_menu("user");
        while((run_login = user_menu(data, username))){
            if(run_login == -1){
                return 0;
            }
        }
    }
    else{
        std::cout << "Invalid input, try again....\n";
        return 1;
    }

    return 1;
}