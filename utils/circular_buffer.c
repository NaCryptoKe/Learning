#include <assert.h>
#include <stdio.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    atomic_size_t start;
    atomic_size_t   end;

    void **buffer;
} ring_buffer;

void push(ring_buffer *R, void *val);
void *pop(ring_buffer *R);
bool is_full(ring_buffer *R);
bool is_empty(ring_buffer *R);

void *producer(void *arg) {
    ring_buffer *R = (ring_buffer *)arg;
    for (int i = 0; i < 6; i++) {
        int *val = malloc(sizeof(int));
        *val = i;
        push(R, val);
    }
    return NULL;
}

void *consumer(void *arg) {
    ring_buffer *R = (ring_buffer *)arg;
    int count = 0;
    while (count < 6) {
        void *val = pop(R);
        if (val != NULL) {
            printf("%d\n", *(int *)val);
            free(val);
            count++;
        } else break;
    }
    return NULL;
}
int main(void) {
    ring_buffer R;
    R.buffer = malloc(sizeof(void *) * MAX_SIZE);
    atomic_store_explicit(&R.start, 0, memory_order_relaxed);
    atomic_store_explicit(&R.end, 0, memory_order_relaxed);
    
    pthread_t t1, t2;

    pthread_create(&t1, NULL, producer, &R);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, consumer, &R);
    pthread_join(t2, NULL);

    free(R.buffer);

    return 0;
}
void push(ring_buffer *R, void *val){
    if (is_full(R)) return;

    size_t start = atomic_load_explicit(&R->start, memory_order_acquire);
    size_t end = atomic_load_explicit(&R->end, memory_order_relaxed);
    size_t index = end % MAX_SIZE;
    R->buffer[index] = val;
    end++;
    atomic_store_explicit(&R->end, end, memory_order_release);
}

void *pop(ring_buffer *R) {
    if(is_empty(R)) return NULL;

    size_t start = atomic_load_explicit(&R->start, memory_order_relaxed);
    size_t end = atomic_load_explicit(&R->end, memory_order_acquire);
    size_t index = start % MAX_SIZE;
    void *val = R->buffer[index];
    start++;
    atomic_store_explicit(&R->start, start, memory_order_release);
    return val;
}

bool is_full(ring_buffer *R) {
    size_t start = atomic_load_explicit(&R->start, memory_order_acquire);
    size_t end = atomic_load_explicit(&R->end, memory_order_relaxed);
    assert(end - start <= MAX_SIZE);
    return (end - start) == MAX_SIZE;
}

bool is_empty(ring_buffer *R) {
    size_t end = atomic_load_explicit(&R->end, memory_order_acquire);
    size_t start = atomic_load_explicit(&R->start, memory_order_relaxed);
    assert(end >= start);
    return (end - start) == 0;
}
