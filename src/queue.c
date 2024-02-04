#include "queue.h"
#include "stdint.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"

simple_queue* init_queue(){
    simple_queue* q = malloc(sizeof(simple_queue));
    if (q == NULL){
        printf("Could not malloc space for queue");
        return NULL;
    }
    q->capacity = QUEUE_MAX_CAPACITY;
    q->front = NULL;
    q->size = 0;
    return q;
}

void free_queue(simple_queue* q){
    node* curr = q->front;
    while (curr){
        node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(q);
}

bool q_emplace_back(simple_queue* queue, const char* text){
    if (queue->size+1>queue->capacity){
        return false;
    }
    node* n = malloc(sizeof(node));
    if (n == NULL){
        printf("Could not malloc space for node");
        return NULL;
    }
    strncpy(n->text, text, MESSAGE_SIZE-1);
    n->text[MESSAGE_SIZE-1] = '\0';
    n->next = NULL;

    // if q is empty add to front
    if (!queue->size){
        queue->front = n;
    } else {
        queue->back->next = n;
    }
    queue->back = n;
    queue->size++;

    #ifdef DEBUG
        printf("==============\n");
        printf("Size: %zu\n", queue->size);
        printf("Capacity: %zu\n", queue->capacity);
        printf("Front*: %p\n", (void *)queue->front);
        printf("Back*: %p\n", (void *)queue->back);
        printf("Enqueued Msg: %s\n", n->text);
        printf("==============\n");
    #endif

    return true;
}

char* q_pop(simple_queue* queue){
    if (queue->size == 0){
        return NULL;
    }

    node* popped_node = queue->front;
    queue->front = popped_node->next;

    char* output = malloc(sizeof(char)*MESSAGE_SIZE);
    if (!output){
        printf("Could not allocate space for message size");
        return NULL;
    }
    strncpy(output, popped_node->text, MESSAGE_SIZE);
    free(popped_node);

    if (!queue->front){
        queue->back = NULL;
    }
    queue->size--;
    #ifdef DEBUG
        printf("==============\n");
        printf("Size: %zu\n", queue->size);
        printf("Capacity: %zu\n", queue->capacity);
        printf("Front*: %p\n", (void*)queue->front);
        printf("Back*: %p\n", (void*)queue->back);
        printf("Dequeued Msg: %s\n", output);
        printf("==============\n");
    #endif
    
    return output;
}

void print_msgs(const simple_queue* q){
    node* curr = q->front;
    int i = 1;
    while (curr){
        printf("==========\n");
        printf("Idx: %d\n", i);
        printf("Msg: %s\n", curr->text);
        printf("==========\n");
        curr = curr->next;
        i++;
    }
}