#include <iostream>

int main() {
    short num_short = 30;
    int num_int = num_short;    // Implicit type casting
    float num_float = 100.75f;
    double num_double = static_cast<int>(num_float); // Explicitly casts float to int, then implicitly changes the int to double

    char letter = 'A';
    int ascii_val = letter;                     // Implicit
    int ascii_value = static_cast<int>(letter); //Explicit

    bool flag = true;

    std::cout << "short: " << num_short << std::endl;
    std::cout << "int: " << num_int << std::endl;
    std::cout << "float: " << num_float << std::endl;
    std::cout << "double: " << num_double << std::endl;
    std::cout << "char: " << letter << ", ASCII Implicit: " << ascii_val << std::endl;
    std::cout << "char: " << letter << ", ASCII Explicit: " << ascii_value << std::endl;
    std::cout << "bool: " << flag << std::endl;
    return 0;
}