#include <iostream>

void fizzbuzz(int num) {
    if (num % 15 == 0) { // Checks if divided by 15 if it's zero, cause dividing by 15 tells us if the number is divisible by both 3 and 5
        // But also we can do if(num % 5 == 0 && num % 3 == 0), but the first one is mathematically simpler
        std::cout << "FizzBuzz" << std::endl;
    } else if (num % 3 == 0) {
        std::cout << "Fizz" << std::endl;
    } else if (num % 5 == 0) {
        std::cout << "Buzz" << std::endl;
    } else {
        std::cout << num << std::endl;
    }
}