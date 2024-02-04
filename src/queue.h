#ifndef QUEUE_H
#define QUEUE_H
#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

#define QUEUE_MAX_CAPACITY 1000
#define MESSAGE_SIZE 1024

typedef struct node {
    char text[MESSAGE_SIZE];
    struct node* next;
} node;

typedef struct {
    node* front;
    node* back;
    size_t size;
    size_t capacity;
    // simple_queue(): front(nullptr), size(0), capacity(MAX_CAPACITY){};
} simple_queue;

/**
 * @brief Mallocs queue, user must call free
*/
simple_queue* init_queue();

void free_queue(simple_queue* q);

/**
 * @brief creates node with malloc (must be freed)
*/
bool q_emplace_back(simple_queue* queue, const char* text);

/**
 * @brief can return NULL
 * frees node from enqueue
*/
char* q_pop(simple_queue* queue);

void print_msgs(const simple_queue* q);
#endif