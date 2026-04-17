int factorial(int num) {
    int factorial = 1;

    if (num != 0 && num != 1) {
        for (int i = 2; i <= num; i++) {
            factorial *= i;
        }
    }

    return factorial;
}