#include <stdio.h>
#include <assert.h>

#define MAX_SIZE 5      // FIXED SIZE OF THE RING BUFFER

typedef struct {
    // Invariant 1: Start and end should never be negative, so we used size_t we can also use unsigned int
    size_t   start;  // Total pops ever; read index = start % MAX_SIZE
    size_t   end;    // Total pushes ever; write index = start % MAX_SIZE

    int      arr[MAX_SIZE];
} circular_queue;

void push(circular_queue *C, int val);
int pop(circular_queue *C);
int is_full(circular_queue *C);
int is_empty(circular_queue *C);

int main(void) {
    circular_queue C;
    C.start = 0;
    C.end = 0;

    printf("FULL: %d, EMPTY: %d\n", is_full(&C), is_empty(&C));
    push(&C, 1);
    push(&C, 2);
    push(&C, 3);
    push(&C, 4);
    push(&C, 4);
    printf("FULL: %d, EMPTY: %d\n", is_full(&C), is_empty(&C));
    pop(&C);
    pop(&C);
    pop(&C);
    printf("FULL: %d, EMPTY: %d\n", is_full(&C), is_empty(&C));
    pop(&C);
    pop(&C);
    printf("FULL: %d, EMPTY: %d\n", is_full(&C), is_empty(&C));
    return 0;
}

void push(circular_queue *C, int val) {
    if (is_full(C)) return;

    size_t index = C->end % MAX_SIZE;
    C->arr[index] = val;
    C->end++;
}

int pop(circular_queue *C) {
    if(is_empty(C)) return -1;

    size_t index = C->start % MAX_SIZE;
    int val = C->arr[index];
    C->start++;
    return val;
}

int is_full(circular_queue *C) {
    assert(C->end - C->start <= MAX_SIZE);      // Invariant 2: The size of the buffer should never overflow than the fixed size given
    size_t current_size = C->end - C->start;
    return current_size == MAX_SIZE;
}

int is_empty(circular_queue *C) {
    assert(C->end >= C->start);                 // Invariant 3: The size of the buffer shouldn't be negative. We can't pop from an empty buffer.
    size_t current_size = C->end - C->start;
    return current_size == 0;
}
