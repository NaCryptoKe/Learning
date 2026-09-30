// This will cause a multiple defintion error
//int buffer_size = 64;
extern int buffer_size;
// We can also do `static int buffer_size = 64;`


void reset_buffer(void);
