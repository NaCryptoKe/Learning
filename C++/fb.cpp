#include <iostream>
#include <ranges>
#include <print>

int main() {
    for (int num : std::views::iota(1, 101)) {
        if (num % 15 == 0) std::println("{}: FizzBuzz", num);
        else if (num % 3 == 0) std::println("{}: Fizz", num);
        else if (num % 5 == 0) std ::println("{}: Buzz", num);
        else std::println("{}", num);
    }

    return 0;
}
