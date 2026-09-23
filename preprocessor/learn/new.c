
void run_demo(void)
{
    puts("========== OBJECT MACROS ==========");

    PRINT(Y);
    PRINT(LIMIT);

    puts("\n========== FUNCTION MACROS ==========");

    PRINT(MAX(10, 20));
    PRINT(MIN(10, 20));
    PRINT(ABS(-35));
    PRINT(SQUARE(5));
    PRINT(SQUARE(2 + 3));

    puts("\n========== TOKEN PASTING ==========");

    int MAKE_VAR(age) = 22;
    int MAKE_VAR(score) = 95;

    PRINT(value_age);
    PRINT(value_score);

    puts("\n========== VARIADIC ==========");

    LOG("Hello from LOG()\n");
    LOG_INFO("Program started.\n");
    LOG_WARN("This is only a demonstration.\n");
    LOG_ERROR("Nothing actually went wrong.\n");

    puts("\n========== BUILT-IN ==========");

    DEBUG();

    puts("========== ARRAY_SIZE ==========");

    int numbers[] = {10,20,30,40,50};

    printf("Array contains %zu elements.\n",
           ARRAY_SIZE(numbers));

    puts("\n========== X-MACROS ==========");

    /* ---------- enum ---------- */

#define X(name) name,

    enum Fruit
    {
        FRUITS
    };

#undef X

    /* ---------- strings ---------- */

#define X(name) #name,

    const char *fruit_names[] =
    {
        FRUITS
    };

#undef X

    /* ---------- print ---------- */

    for (size_t i = 0; i < ARRAY_SIZE(fruit_names); i++)
        printf("%s\n", fruit_names[i]);
}
