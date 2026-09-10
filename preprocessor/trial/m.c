#define STRINGIZE(x) #x
#define CONCAT(a, b) a##b
int CONCAT(my, Var) = 5;
const char *s = STRINGIZE(hello world);
