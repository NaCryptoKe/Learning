/*
* int x; at file scope is called a 
* TENTATIVE DEFINITION
* so how many times we write int x, the compiler only sees
* one of it, if they never get initialized that is.

*/
int x;
int x;
int main(void){return x;}
