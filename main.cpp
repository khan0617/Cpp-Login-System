#include <fstream>
#include <string>
#include "user_database.h"

int main(){
    std::ifstream in("user.json");
    json data = json::parse(in);
    std::cout << "Welcome to the user database! Type \"quit\" at any time to end the program.\n";
}