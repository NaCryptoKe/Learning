#include <stdio.h>

int main(void)
{
    int n1, n2, n3;
    float f1, f2;

    /* ==========================================
     * (a) "%d" versus " %d"
     * ==========================================
     * Behavior: Practically identical for a single value.
     * Both skip leading whitespace automatically.
     */
    printf("--- Test (a): %%d vs ' %%d' ---\n");
    printf("Enter an integer (e.g.,   42): ");
    scanf("%d", &n1); // Automatically skips the spaces before 42
    printf("Read with '%%d': %d\n\n", n1);

    // Clear input buffer newline
    while (getchar() != '\n');


    /* ==========================================
     * (b) "%d-%d-%d" versus "%d -%d -%d"
     * ==========================================
     * Behavior: 
     * - "%d-%d-%d" strictly requires hyphens touching numbers (e.g., 1-2-3).
     * - "%d -%d -%d" allows spaces around the hyphens (e.g., 1 - 2 - 3).
     */
    printf("--- Test (b): Hyphen spacing ---\n");
    printf("Try entering: 1 - 2 - 3 using \"%%d-%%d-%%d\" (it will fail or partial-match)\n");
    printf("Enter three hyphen-separated integers: ");
    
    // Using the stricter one to demonstrate distinction:
    if (scanf("%d-%d-%d", &n1, &n2, &n3) == 3) {
        printf("Success! Read: %d, %d, %d\n\n", n1, n2, n3);
    } else {
        printf("Failed to match strict format! (Try 1-2-3 instead)\n\n");
    }

    while (getchar() != '\n');


    /* ==========================================
     * (c) "%f" versus "%f " (Trailing Space Trap)
     * ==========================================
     * Behavior:
     * - "%f" leaves the trailing newline in the buffer.
     * - "%f " (with a trailing space) hangs and waits for a non-whitespace 
     *   character before it finishes executing.
     */
    printf("--- Test (c): Trailing Space Trap ---\n");
    printf("Enter a float (e.g., 3.14 and press Enter): ");
    
    // Notice the trailing space inside the quotes below:
    // scanf("%f ", &f1); 
    // ^ WARNING: If you uncomment the line above, scanf will hang after you press Enter,
    // waiting for you to type another non-whitespace character!
    
    scanf("%f", &f1); // Safe version
    printf("Read float safely: %.2f\n\n", f1);

    while (getchar() != '\n');


    /* ==========================================
     * (d) "%f,%f" versus "%f, %f"
     * ==========================================
     * Behavior: Identical in practice. The space after the comma 
     * in "%f, %f" is redundant because the second %f automatically 
     * skips leading whitespace anyway.
     */
    printf("--- Test (d): Comma spacing ---\n");
    printf("Enter two comma-separated floats with a space (e.g., 3.14, 2.0): ");
    scanf("%f, %f", &f1, &f2); // Works for "3.14,2.0" and "3.14, 2.0"
    printf("Read floats: %.2f and %.2f\n", f1, f2);

    return 0;
}
