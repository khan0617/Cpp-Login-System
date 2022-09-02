#include <fstream>
#include <string>
#include "user_database.h"

int main(){
    std::ifstream in("users.json");
    json data = json::parse(in);
    std::cout << "Welcome to the user database! Type \"quit\" at any time to end the program.\n";
    while(main_menu(data));
    std::ofstream out("users.json");
    out << data.dump(4) << std::endl;
    std::cout << "Goodbye!" << std::endl;
}