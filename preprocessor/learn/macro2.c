/*
 * The C pipleine has 5 operations/stages
 *
 * 1. Preprocessing: takes in *.c and gives back a *.o file. `gcc -E *.c -o *.i`
 * Comment Removal
 * Conditional Compilation "#ifdef" "#ifndef" and "#if"
 * Macro Expansion
 * File inclusion
 *
 * 2. Compilation: takes in *.i and spits out a *.s (assembly). `gcc -S *.i -o *.s
 * Parsing & Syntax checking
 * Optimization
 * Translation: Converting the high-level C logic into architecture specific assembly instructions
 *
 * 3. Assembly: takes in *.s and spits out *.o (object code). `gcc -c *.s -o *.o
 * Coverts text-based assembly commands into raw binary
 * Binary translation
 * Object File Generation
 *
 * 4. Linking: stitches together all individual object files. *.o -> executable. `gcc *.o -o main`
 * Symbol resolution: connects function calls
 * Memory addressing: determine the concrete memory layout
 * Output: create the executable binary
 */
#define X 50

int main ()
{
    int x = X;
    x += X;
}
